#include "stdint.h"


//#include "board.hpp"
#include "fsm_types_capi.h"
#include "fsm_timer_capi.h"
#include "fsm.h"
#include "am3358zcz_pins_capi.h"

//-------------------------------------------------------------------------------------------------
// FSM test_fsm_c:
//-------------------------------------------------------------------------------------------------
fsm_t  test_fsm_c;

#define WAIT_DELAY_STEP (3)

static float last_t = 0;
static float  ms = 0;
static  uint8_t repeats = 1;

static uint32_t m_stage_before_wait = 0;

static bool test_fsm_init(fsm_t* fsm)
{
    action_cmd* cmd = (action_cmd*) fsm->params;

    repeats = cmd->repetitions;
    m_stage_before_wait = 0;
    
    pin_set((e_AM3358_pins)DBG_PIN3_pin);
    last_t = fsm_tmr_get_ms(); 

    return false;
}

static bool test_fsm(fsm_t* fsm)
{
    repeats--;    

    if (repeats)
    {
        pin_toggle((e_AM3358_pins)USR_LED_2_pin);
        
        m_stage_before_wait = fsm->stage;
        fsm_go_to(fsm, WAIT_DELAY_STEP);
    }    

    return false;
}

static bool test_fsm_c_end(fsm_t* fsm)
{
    pin_set((e_AM3358_pins)DBG_PIN3_pin);   
    pin_clear((e_AM3358_pins)USR_LED_2_pin);

    repeats = 0;    
    m_stage_before_wait = 0;
    
    fsm_finish(fsm);
    
    ms = fsm_tmr_get_ms();
    ms = 0;
    last_t = 0;

    pin_clear((e_AM3358_pins)DBG_PIN3_pin);

    return false;
}

static bool test_fsm_wait_delay(fsm_t* fsm)
{
    static uint32_t delay = 0;
    action_cmd* cmd = (action_cmd*) fsm->params;
    
    pin_toggle((e_AM3358_pins)DBG_PIN3_pin);

    if(delay == 0u)
        delay = (uint32_t)(cmd->rep_delay/FSM_TIME_DELTA); 
    
    delay--;
    
    if(delay == 0u)
      fsm_go_to(fsm, m_stage_before_wait);
    else
      fsm_repeat_step(fsm);      

    return false;
}

const fsm_step_t test_fsm_c_prog[] = 
{
     /*0*/  {1, 5,     (void const*) test_fsm_init},
     /*1*/  {1, 5,     (void const*) test_fsm},
     /*2*/  {1, 5,     (void const*) test_fsm_c_end},
     /*3*/  {1, 5,     (void const*) test_fsm_wait_delay},
            {0}
};
//-------------------------------------------------------------------------------------------------
