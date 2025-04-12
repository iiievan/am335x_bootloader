#ifndef __AM335x_UART_HPP
#define __AM335x_UART_HPP

#include <stdint.h>
#include "utils.h"
#include "UART.hpp"
#include "INTC.h"
#include "paired_buffer.h"
#include "ring_buffer.hpp"
#include "sw_Timer.h"

class sw_Timer;
extern sw_Timer RX_end_timer;
extern void RX_end_callback(void * p_Obj);

class am335x_uart
{
    enum e_UART_RX_fsm_sts : uint32_t
    {
        RX_IDLE             = 0x0,  // nothing to happen, ready to operation
        RX_IN_PROGESS       = 0x1,  // RX transaction started and in progress 
        RX_CHUNK_RECEIVED   = 0x2,  // one of two of RX paired buffer is full
        RX_TOUT_IS_OUT      = 0x3,  // timeout after the last received byte has expired, the reception is over
        RX_STOPPED          = 0x4   // receiver stopped 
    };
    
    friend void  RX_end_callback(void * p_Obj);
    
public:
            am335x_uart(REGS::UART::AM335x_UART_Type *p_uart_regs);
           ~am335x_uart() {}
     
      void  module_reset();
      void  FIFO_configure_no_DMA(uint8_t tx_trig_lvl, uint8_t rx_trig_lvl);
      void  FIFO_configure_DMA_RxTx(uint8_t tx_trig_lvl, uint8_t rx_trig_lvl);
      
REGS::UART::FCR_reg_t  FIFO_config(REGS::UART::SCR_reg_t  cfg_scr, 
                                   REGS::UART::TLR_reg_t  fifo_trigger_lvl, 
                                   REGS::UART::FCR_reg_t  cfg_fcr);

      void  BAUD_set(unsigned int baud_rate);
  uint32_t  reg_config_mode_enable(REGS::UART::e_CONFIG_MODE mode_flag);
      //void  line_char_config(uint32_t wlen_stb_flag, uint32_t parity_flag);
      // Programming the Line Characteristics. 
      void  char_len_config(REGS::UART::e_CHAR_LENGHT len);
      void  stop_bit_config(REGS::UART::e_STOP_BIT stop_bit);
      void  parity_config(REGS::UART::e_LCR_PARITY parity);

  REGS::UART::e_MODESELECT  operating_mode_select(REGS::UART::e_MODESELECT mode_flag);
  uint32_t  divisor_val_compute(uint32_t  module_clk,
                                uint32_t  baud_rate,
                REGS::UART::e_MODESELECT  mode_flag,
                                uint32_t  mir_over_samp_rate);
  uint32_t  divisor_latch_write(uint32_t divisor_value);
      void  divisor_latch_enable();
      void  divisor_latch_disable();
      void  reg_conf_mode_restore(uint32_t lcr_reg_value);
      void  break_ctl(bool break_state);
      void  parity_mode_set(uint32_t parity_flag);
  uint32_t  parity_mode_get();
  
 REGS::UART::e_UART_INSTANCE_NUM  get_UART_inst_number();
 REGS::INTC::e_INT_ID  get_UART_sys_interrupt();

      void  DMA_enable(REGS::UART::e_SCR_DMA_MODE dma_mode_flag);
      void  DMA_disable();
      void  FIFO_register_write(REGS::UART::FCR_reg_t  cfg_fcr);
  uint32_t  enhan_func_enable();
      void  enhan_func_bit_val_restore(bool enhan_fn_bit_val);
  uint32_t  sub_config_MSRSPR_mode_en();
  uint32_t  sub_config_TCRTLR_mode_en();
  uint32_t  sub_config_XOFF_mode_en();
      void  TCRTLR_bit_val_restore(uint32_t tcr_tlr_bit_val);
      void  int_enable(REGS::UART::e_UART_IT_EN int_flag);
      void  int_disable(REGS::UART::e_UART_IT_EN int_flag);
  uint32_t  space_avail();
  uint32_t  chars_avail();
  uint32_t  char_put_non_blocking(uint8_t byte_write);
      char  char_get_non_blocking();
      char  char_get();
       int  char_get_timeout(uint32_t time_out_val);
      void  char_put(uint8_t byte_tx);
      void  FIFO_char_put(uint8_t byte_tx);
      char  FIFO_char_get();
  uint32_t  FIFO_write(uint8_t *p_Buf, uint32_t num_tx_bytes);
  uint32_t  RX_error_get();
  uint32_t  int_identity_get();
      bool  int_pending_status_get();
      bool  FIFO_enable_status_get();
      void  auto_RTS_auto_CTS_control(uint32_t auto_cts_control, uint32_t auto_rts_control);
      void  special_char_detect_control(uint32_t control_flag);
      void  software_flow_ctrl_opt_set(uint32_t sw_flow_ctrl);
      void  pulse_shaping_control(uint32_t shape_control);
      
      void  idle_mode_configure(REGS::UART::e_IDLEMODE mode_flag);
      void  wakeup_control(uint32_t control_flag);
      void  auto_idle_mode_control(uint32_t mode_flag);
      void  flow_ctrl_trig_lvl_config(uint32_t rts_halt_flag, uint32_t rts_start_flag);
      void  XON1XOFF1_val_program(uint8_t xon1_value, uint8_t xoff1_value);
      void  XON2XOFF2_val_program(uint8_t xon2_value, uint8_t xoff2_value);
      void  XON_any_feature_control(uint32_t control_flag);
      void  loopback_mode_control(uint32_t control_flag);
      void  modem_control_set(uint32_t mode_flag);
      void  modem_control_clear(uint32_t mode_flag);
  uint32_t  modem_ctatus_get();
  uint32_t  modem_ctatus_change_check();
      void  resume_operation();
      void  wakeup_events_enable(uint32_t wakeup_flag);
      void  wakeup_events_disable(uint32_t wakeup_flag);
      void  FIFO_trig_lvl_gran_control(uint32_t rx_FIFO_gran_ctrl, uint32_t tx_FIFO_gran_ctrl);
      void  DSR_interrupt_control(uint32_t control_flag);
      void  TX_empty_int_control(uint32_t control_flag);
      void  RXCTSDSR_wakeup_configure(uint32_t wake_up_flag);
  uint32_t  RXCTSDSR_transition_status_get();
      void  DMA_counter_reset_control(uint32_t control_flag);
      bool  TX_FIFO_full_status_get();
  uint32_t  TX_FIFO_level_get();
  uint32_t  RX_FIFO_level_get();
  uint32_t  autobaud_parity_get();
  uint32_t  autobaud_word_len_get();
  uint32_t  autobaud_speed_get();
      void  scratchpad_reg_write(uint32_t scratch_value);
  uint32_t  scratchpad_reg_read();
  uint32_t  module_version_number_get();
      void  TX_DMA_threshold_control(bool thrs_ctrl_flag);
      void  TX_DMA_threshold_val_config(uint32_t thrs_value);
      
       bool  is_RX_data_rdy(ring_buffer<char,REGS::UART::RX_FIFO_MAX*4>* p_Data); 
                  
       void  rx_irq(void);                  // need to be placed in IRQ_Handler if RX used
       void  tx_irq(void);                  // need to be placed in IRQ_Handler if TX used
       
       void  write(const char *data, size_t len);
       
paired_buffer<char, REGS::UART::RX_FIFO_MAX>  m_RX_data;   // cumulative received data buffer
paired_buffer<char, REGS::UART::TX_FIFO_MAX>  m_TX_data;   // storage data buffer for sending
       
private:
    REGS::UART::AM335x_UART_Type &m_UART_regs; 
        
                            void  m_Start_TX(size_t amount);
                            void  m_Start_RX(size_t amount);
                            bool  m_TX_busy;
               e_UART_RX_fsm_sts  m_RX_sts;
};

extern am335x_uart uart_0;

#endif //__AM335x_UART_HPP