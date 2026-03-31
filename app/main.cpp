#include <stdint.h>
#include "init.h"

/*=======================================================================*/
/*  All Structures and Common Constants                                  */
/*=======================================================================*/

/*=======================================================================*/
/*  Definition of all global Data                                        */
/*=======================================================================*/

/*=======================================================================*/
/*  Definition of all local Data                                         */
/*=======================================================================*/
static const uint32_t d  = 7;
static const float    fd = 5.3f;
static uint32_t       dd = 8;

/* Must be 0, BSS must be cleared by the startup */
static uint32_t       must_zero_after_startup;

/*=======================================================================*/
/*  All code exported                                                    */
/*=======================================================================*/

/*************************************************************************/
/*  main                                                                 */
/*************************************************************************/
int main (void)
{
  uint32_t a  = 1;
  uint32_t b  = 2;
  uint32_t c  = 0;
  float    fa = 1.3f;
  float    fb = 2.7f;
  float    fc = 3.9f;

   init_board();

  fa = fa + fd;
  a  = a + d + dd + must_zero_after_startup;

  /* A must be 16 here */
  if (a != 16) while (1) {};

  while (1)
  {
    a++;
    b++;
    c = a + b;

    fa = fa + 2.6f;
    fb = fb + 1.67f;
    fc = fa + fb;
  }

  /*
   * Prevent compiler warnings
   */
  (void)fc;
  (void)c;

  /*
   * This return here make no sense.
   * But to prevent the compiler warning:
   * "return type of 'main' is not 'int'
   * we use an int as return :-)
   */
  return(0);
} /* main */