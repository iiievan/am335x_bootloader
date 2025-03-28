/* Copyright (c) 2023  Hunter Whyte */
#ifndef _UART_H
#define _UART_H

#include "common.h"

#ifdef _cplusplus
extern "C" {
#endif

#define UART0_BASE          0x44E09000

#define THR_OFFSET          0x00000000
#define RHR_OFFSET          0x00000000
#define DLL_OFFSET          0x00000000
#define IER_IRDA_OFFSET     0x00000004
#define IER_CIR_OFFSET      0x00000004
#define IER_UART_OFFSET     0x00000004
#define DLH_OFFSET          0x00000004
#define EFR_OFFSET          0x00000008
#define IIR_UART_OFFSET     0x00000008
#define IIR_CIR_OFFSET      0x00000008
#define FCR_OFFSET          0x00000008
#define IIR_IRDA_OFFSET     0x00000008
#define LCR_OFFSET          0x0000000C
#define MCR_OFFSET          0x00000010
#define XON1_ADDR1_OFFSET   0x00000010
#define XON2_ADDR2_OFFSET   0x00000014
#define LSR_CIR_OFFSET      0x00000014
#define LSR_IRDA_OFFSET     0x00000014
#define LSR_UART_OFFSET     0x00000014
#define TCR_OFFSET          0x00000018
#define MSR_OFFSET          0x00000018
#define XOFF1_OFFSET        0x00000018
#define SPR_OFFSET          0x0000001C
#define TLR_OFFSET          0x0000001C
#define XOFF2_OFFSET        0x0000001C
#define MDR1_OFFSET         0x00000020
#define MDR2_OFFSET         0x00000024
#define TXFLL_OFFSET        0x00000028
#define SFLSR_OFFSET        0x00000028
#define RESUME_OFFSET       0x0000002C
#define TXFLH_OFFSET        0x0000002C
#define RXFLL_OFFSET        0x00000030
#define SFREGL_OFFSET       0x00000030
#define SFREGH_OFFSET       0x00000034
#define RXFLH_OFFSET        0x00000034
#define BLR_OFFSET          0x00000038
#define UASR_OFFSET         0x00000038
#define ACREG_OFFSET        0x0000003C
#define SCR_OFFSET          0x00000040
#define SSR_OFFSET          0x00000044
#define EBLR_OFFSET         0x00000048
#define MVR_OFFSET          0x00000050
#define SYSC_OFFSET         0x00000054
#define SYSS_OFFSET         0x00000058
#define WER_OFFSET          0x0000005C
#define CFPS_OFFSET         0x00000060
#define RXFIFO_LVL_OFFSET   0x00000064
#define TXFIFO_LVL_OFFSET   0x00000068
#define IER2_OFFSET         0x0000006C
#define ISR2_OFFSET         0x00000070
#define FREQ_SEL_OFFSET     0x00000074
#define MDR3_OFFSET         0x00000080
#define TX_DMA_THRSH_OFFSET 0x00000084

#define UART0_THR           (UART0_BASE + THR_OFFSET)
#define UART0_RHR           (UART0_BASE + RHR_OFFSET)
#define UART0_DLL           (UART0_BASE + DLL_OFFSET)
#define UART0_IER_IRDA      (UART0_BASE + IER_IRDA_OFFSET)
#define UART0_IER_CIR       (UART0_BASE + IER_CIR_OFFSET)
#define UART0_IER_UART      (UART0_BASE + IER_UART_OFFSET)
#define UART0_DLH           (UART0_BASE + DLH_OFFSET)
#define UART0_EFR           (UART0_BASE + EFR_OFFSET)
#define UART0_IIR_UART      (UART0_BASE + IIR_UART_OFFSET)
#define UART0_IIR_CIR       (UART0_BASE + IIR_CIR_OFFSET)
#define UART0_FCR           (UART0_BASE + FCR_OFFSET)
#define UART0_IIR_IRDA      (UART0_BASE + IIR_IRDA_OFFSET)
#define UART0_LCR           (UART0_BASE + LCR_OFFSET)
#define UART0_MCR           (UART0_BASE + MCR_OFFSET)
#define UART0_XON1_ADDR1    (UART0_BASE + XON1_ADDR1_OFFSET)
#define UART0_XON2_ADDR2    (UART0_BASE + XON2_ADDR2_OFFSET)
#define UART0_LSR_CIR       (UART0_BASE + LSR_CIR_OFFSET)
#define UART0_LSR_IRDA      (UART0_BASE + LSR_IRDA_OFFSET)
#define UART0_LSR_UART      (UART0_BASE + LSR_UART_OFFSET)
#define UART0_TCR           (UART0_BASE + TCR_OFFSET)
#define UART0_MSR           (UART0_BASE + MSR_OFFSET)
#define UART0_XOFF1         (UART0_BASE + XOFF1_OFFSET)
#define UART0_SPR           (UART0_BASE + SPR_OFFSET)
#define UART0_TLR           (UART0_BASE + TLR_OFFSET)
#define UART0_XOFF2         (UART0_BASE + XOFF2_OFFSET)
#define UART0_MDR1          (UART0_BASE + MDR1_OFFSET)
#define UART0_MDR2          (UART0_BASE + MDR2_OFFSET)
#define UART0_TXFLL         (UART0_BASE + TXFLL_OFFSET)
#define UART0_SFLSR         (UART0_BASE + SFLSR_OFFSET)
#define UART0_RESUME        (UART0_BASE + RESUME_OFFSET)
#define UART0_TXFLH         (UART0_BASE + TXFLH_OFFSET)
#define UART0_RXFLL         (UART0_BASE + RXFLL_OFFSET)
#define UART0_SFREGL        (UART0_BASE + SFREGL_OFFSET)
#define UART0_SFREGH        (UART0_BASE + SFREGH_OFFSET)
#define UART0_RXFLH         (UART0_BASE + RXFLH_OFFSET)
#define UART0_BLR           (UART0_BASE + BLR_OFFSET)
#define UART0_UASR          (UART0_BASE + UASR_OFFSET)
#define UART0_ACREG         (UART0_BASE + ACREG_OFFSET)
#define UART0_SCR           (UART0_BASE + SCR_OFFSET)
#define UART0_SSR           (UART0_BASE + SSR_OFFSET)
#define UART0_EBLR          (UART0_BASE + EBLR_OFFSET)
#define UART0_MVR           (UART0_BASE + MVR_OFFSET)
#define UART0_SYSC          (UART0_BASE + SYSC_OFFSET)
#define UART0_SYSS          (UART0_BASE + SYSS_OFFSET)
#define UART0_WER           (UART0_BASE + WER_OFFSET)
#define UART0_CFPS          (UART0_BASE + CFPS_OFFSET)
#define UART0_RXFIFO_LVL    (UART0_BASE + RXFIFO_LVL_OFFSET)
#define UART0_TXFIFO_LVL    (UART0_BASE + TXFIFO_LVL_OFFSET)
#define UART0_IER2          (UART0_BASE + IER2_OFFSET)
#define UART0_ISR2          (UART0_BASE + ISR2_OFFSET)
#define UART0_FREQ_SEL      (UART0_BASE + FREQ_SEL_OFFSET)
#define UART0_MDR3          (UART0_BASE + MDR3_OFFSET)
#define UART0_TX_DMA_THRSH  (UART0_BASE + TX_DMA_THRSH_OFFSET)
  
void uart_init(void (*callback)(char));
void uart_putc(char c);
void uart_puts(char* c);
void uart_hexdump(uint32_t val);
char uart_getc(void);
void uart_isr(void);

#ifdef _cplusplus
}
#endif

#endif /* _UART_H */