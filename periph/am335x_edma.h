#pragma once

#include "EDMA.hpp"

class AM335x_EDMA
{
public:
    REGS::EDMA::e_REGION_ID  region_id;
void (*cb_fx[REGS::EDMA::AM335X_DMACH_MAX]) (uint32_t tcc);  // function callbacks for REGS::EDMA channels and events
             
public:
              AM335x_EDMA()
                : m_EDMA3CC_regs(*(REGS::EDMA::AM335X_EDMA3CC_regs)),
                m_EDMA3TC0_regs(*(REGS::EDMA::AM335X_EDMA3TC0_regs)),
                m_EDMA3TC1_regs(*(REGS::EDMA::AM335X_EDMA3TC1_regs)),
                m_EDMA3TC2_regs(*(REGS::EDMA::AM335X_EDMA3TC2_regs)) 
              { 
                #ifdef _TMS320C6X        
                    region_id = REGS::EDMA::REGION_1;   // For DSP, region_id is assigned here and used globally in the driver
                #else   
                    region_id = REGS::EDMA::REGION_0;   // FOR ARM, region_id is assigned here and used globally in the driver
                #endif
              }
             ~AM335x_EDMA() { }

        void  init(REGS::EDMA::e_DMA_QUEUE que_num);
        void  set_non_idle_mode();
        void  enable_ch_in_shadow_reg(REGS::EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num);
        void  disable_ch_in_shadow_reg(REGS::EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num);
        void  map_ch_to_evtQ(REGS::EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num, REGS::EDMA::e_DMA_QUEUE evt_Qnum);
        void  unmap_ch_to_evtQ(REGS::EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num);
        void  map_QDMA_ch_to_paRAM(uint32_t ch_num, uint32_t *paRAM_id);
        void  set_QDMA_trig_word(uint32_t ch_num, uint8_t trig_word);
        void  clr_miss_evt(uint32_t ch_num);
        void  QDMA_clr_miss_evt(uint32_t ch_num);
        void  clr_CCERR(uint32_t flags);
        void  set_evt(uint32_t ch_num);
        void  clr_evt(uint32_t ch_num);
        void  enable_DMA_evt(uint32_t ch_num);
        void  disable_DMA_evt(uint32_t ch_num);
        void  enable_QDMA_evt(uint32_t ch_num);
        void  disable_QDMA_evt(uint32_t ch_num);
    uint32_t  get_intr_status();
        void  enable_evt_intr(uint32_t ch_num);
        void  disable_evt_intr(uint32_t ch_num);
        void  clr_intr(uint32_t value);
REGS::EDMA::paRAM_entry_t* get_paRAM(uint32_t paRAM_id);
REGS::EDMA::paRAM_entry_t* QDMA_get_paRAM(uint32_t paRAM_id);
        void  set_paRAM(uint32_t ch_num, REGS::EDMA::paRAM_entry_t* new_paRAM);
        void  QDMA_set_paRAM(uint32_t paRAM_id, REGS::EDMA::paRAM_entry_t* new_paRAM);
        void  QDMA_set_paRAM_entry(uint32_t paRAM_id, uint32_t paRAM_entry, uint32_t new_paRAM_entry_val);
    uint32_t  QDMA_get_paRAM_entry(uint32_t paRAM_id, uint32_t paRAM_entry);
        bool  request_channel(REGS::EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num, uint32_t tcc_num, REGS::EDMA::e_DMA_QUEUE evt_Qnum);
        bool  free_channel(REGS::EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num, uint32_t trig_mode, uint32_t tcc_num, REGS::EDMA::e_DMA_QUEUE evt_Qnum);
        bool  enable_transfer(uint32_t ch_num, uint32_t trig_mode);
        bool  disable_transfer(uint32_t ch_num, uint32_t trig_mode);
        void  clear_error_bits(uint32_t ch_num, REGS::EDMA::e_DMA_QUEUE evt_Qnum);
    uint32_t  get_CCERR_status();
    uint32_t  get_ERR_intr_status();
 REGS::EDMA::QEMR_reg_t  QDMA_get_ERR_intr_status();
        void  CCERR_evaluate();
        void  deinit(uint32_t que_num);
    uint32_t  version_get(void) const { return 1; } // This returns a number '2' which is unique to EDMA IP in AM335x.
    uint32_t  peripheral_id_get();
    uint32_t  intr_status_high_get();
    uint32_t  ERR_intr_high_status_get();
        void  channel_to_param_map(uint32_t channel, uint32_t param_set);
        void  context_save(REGS::EDMA::EDMACONTEXT_t *p_edma_cntx);
        void  context_restore(REGS::EDMA::EDMACONTEXT_t *p_edma_cntx);
        
        
private:
    REGS::EDMA::AM335x_EDMA3CC_Type &m_EDMA3CC_regs;
    REGS::EDMA::AM335x_EDMA3TC_Type &m_EDMA3TC0_regs;
    REGS::EDMA::AM335x_EDMA3TC_Type &m_EDMA3TC1_regs;
    REGS::EDMA::AM335x_EDMA3TC_Type &m_EDMA3TC2_regs;
};

extern AM335x_EDMA eDMA;