#include "project.h"

#define TIMER_PERIOD_TICKS (1000u) 

volatile uint32_t isr_timer_count = 0u;


CY_ISR(Timer_ISR_Handler)
{
    Pin_ISR_Write((uint8)(!Pin_ISR_Read()));
    
    isr_timer_count++;
    
    
    Timer_1_ClearInterrupt(Timer_1_INTR_MASK_TC);
}


CY_ISR(Button_Main_Handler)
{

    uint8 current_state = Pin_Main_Read();
    Pin_Main_Write((uint8)(!current_state));
    
    Button_ClearInterrupt();
}

int main(void)
{
    CyGlobalIntEnable; 

    Clock_1_Start();
    Timer_1_Start();
    Timer_1_WritePeriod(TIMER_PERIOD_TICKS);
    Timer_1_SetInterruptMode(Timer_1_INTR_MASK_TC);
    
    
    isr_Timer_StartEx(Timer_ISR_Handler);
    isr_Button_StartEx(Button_Main_Handler);

}