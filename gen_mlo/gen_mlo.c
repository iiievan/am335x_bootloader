/* Copyright (c) 2023  Hunter Whyte
  See page 5075 of AM355x TRM "26.1.10 Image Format"
  A header containing the destination address and size of the binary image must
  be present. This executable generates the header and writes out a modified
  binary with the header present. The size is the size of the executable 
  provided in bytes, the destination address is alway 0x402f0400 - which is 
  the start of internal SRAM - see AM335x TRM table 2-1.
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* 1.To compile with MSVC and avoid safety warnings about fopen function
 *   go to project settings->C/C++->preprocessor in field preprocessor definitions
 *   add _CRT_SECURE_NO_WARNINGS;
 * 2. to use the resulting gen_mlo.exe in IAR postbuild actions go to 
 *   project settings->Build Actions. Add in field Post-build command line:
 *   "$PROJ_DIR$\ti_image\gen_mlo.exe"  "$TARGET_BPATH$.bin" "$TARGET_DIR$\MLO"
 * 3. To use standalone from cmd put compiled binary am335x_bootloader.bin from output IAR folder
 *    to folder where gen_mlo.exe is and run from cmd .\gen_mlo.exe am335x_bootloader.bin MLO
 * 4. For normal operation of the secondary bootloader it is necessary to format the card in FAT32 
 *    file system with sector size 512 in windows explorer and place MLO file on it.
 *    It is also very important that SYSTEMSTART section and Entry symbol in it is located at 
 *    address 0x402f0400. To do this you need to write in the .icf file:
 *
 *    place at address mem:__ICFEDIT_region_RAM_start__
 *                       { readonly section SYSTEMSTART };
 *
 *     and check .map file after compilation:
 *      ...
 *      CSTACK$$Limit           0x402f'4010          --   Gb  - Linker created -
 *      Entry                   0x402f'0400         Code  Gb  init.o [5]
 *      FIQHandler              0x402f'2748         Code  Gb  exceptionhandler.o [5]
 *      ...
 */

int main(int argc, char** argv) {

  if (argc != 3) {
    printf("argument of binary executable and destination required\n");
    printf("usage: ./gen_mlo <input.bin> <output.img>\n");
    return 0;
  }

  FILE* fin;
  fin = fopen(argv[1], "rb");
  fseek(fin, 0L, SEEK_END);
  int image_size = ftell(fin);
  printf("provided image size in bytes: %d\n", image_size);
  fseek(fin, 0, SEEK_SET);

  FILE* fout;
  fout = fopen(argv[2], "wb");

  /* after the TOC the device expects the GP Header (see TRM 26.1.10.2) */
  /* 0x00: size of MLO binary */
  fwrite(&image_size, 4, 1, fout);
  /* 0x04: address of start of image destination/code entry point
    load code into the start of internal SRAM (see TRM table 2-1) */
  uint32_t sram_start = 0x402f0400;
  fwrite(&sram_start, 4, 1, fout);
  /* append binary to end of this */
  uint8_t* image = (uint8_t*)malloc(image_size);
  fread(image, image_size, 1, fin);
  fwrite(image, image_size, 1, fout);

  fclose(fout);
  fclose(fin);

  return 0;
}
