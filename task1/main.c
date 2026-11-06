#include "project.h"

/* Варіант 1: Clock_1 = 1 МГц (тік 1 мкс), період переривання 1 мс -> 1000 тіків */
#define TIMER_PERIOD_TICKS (1000u)

volatile uint32_t isr_timer_count = 0u;

CY_ISR(Timer_ISR_Handler)
{

Pin_ISR_Write((uint8)(!Pin_ISR_Read()));

isr_timer_count++;

Timer_1_ClearInterrupt(Timer_1_INTR_MASK_TC);
}

int main(void)
{
CyGlobalIntEnable;

Clock_1_Start();
Timer_1_Start();
Timer_1_WritePeriod(TIMER_PERIOD_TICKS);
Timer_1_SetInterruptMode(Timer_1_INTR_MASK_TC);

isr_Timer_StartEx(Timer_ISR_Handler);

   for(;;)
   {
   Pin_Main_Write(1u);
   CyDelay(3);
   Pin_Main_Write(0u);
   CyDelay(3);
   }
}
