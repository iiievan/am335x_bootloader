#include"sw_Timer.h"

sw_Timer::sw_Timer(uint64_t preset, sys_timer<SYST_t>& s_Source, tmrCallback clb) 
: m_timeSource(s_Source)
{  
    set_period(preset);
    set_callback(clb); 
}

sw_Timer& sw_Timer::update()
{ 
    m_Timer = m_timeSource.get_ms() + m_Preset; 

    return *this;
}

sw_Timer& sw_Timer::start()
{
    // start timer.
    // while m_CountPprogress is true off_delay in other places in program not working;
    if(!m_CountPprogress)
    {
          m_CountPprogress = true;
          update();
    } 
    
    return *this;
}

bool  sw_Timer::on_delay(void * p_Obj)
{
    bool result = false;

    if(m_CountPprogress)
    {   

        if (m_timeSource.get_ms() > m_Timer)
        {
            // порядок следования не менять
            // вначале остановка потом вызов функции
            // т.к. в функции его может потребоваться запустить заново
            stop();
            m_Callback(p_Obj);
            // return false all the time after delay
            result = true;            
        }
    }

    return result;
}

bool  sw_Timer::off_delay(void * p_Obj)
{
    bool result = false;

    if(m_CountPprogress)
    {   
        // return true all the time delay
        result  = true;
        
       // порядок следования не менять
       // вначале остановка потом вызов функции
       // т.к. в функции его может потребоваться запустить заново
        if (m_timeSource.get_ms() > m_Timer)
            stop();
        
         m_Callback(p_Obj);
    }

    return result;
}