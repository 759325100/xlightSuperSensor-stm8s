#include <stm8s.h>
#include "timer_4.h"
#include "_global.h"

uint8_t TIM4_Timer10ms = 0;

uint16_t TIM4_TimingDelay = 0;
uint8_t TIM4_TimingDelayUs = 0;

TM4_CallBack_t TIM4_1ms_handler = NULL;
TM4_CallBack_t TIM4_10ms_handler = NULL;

void Time4_Init(void) {
  // Interval = 8us*125 = 1ms
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 124);
  TIM4_PrescalerConfig(TIM4_PRESCALER_128, TIM4_PSCRELOADMODE_IMMEDIATE);
  TIM4_ARRPreloadConfig(ENABLE);
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  TIM4_Cmd(ENABLE);
}

/*INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{
  if( TIM4_1ms_handler ) (*TIM4_1ms_handler)();
  
  if(TIM4_Timer10ms > 0) {
    TIM4_Timer10ms--;
  } else {
    // Reset and go
    TIM4_Timer10ms = 10;
    if( TIM4_10ms_handler ) (*TIM4_10ms_handler)();
  }

  TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
}*/

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{ 
  if(TIM4_TimingDelay > 0)
  {
    TIM4_TimingDelay--;
  }
  
  if(TIM4_TimingDelayUs > 0)
  {
    TIM4_TimingDelayUs--;
  }
  TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
  if(TIM4_TimingDelay == 0 && TIM4_TimingDelayUs == 0)
  {
    TIM4_Cmd(DISABLE);
  }
}

void Delayms(uint16_t _ms) {
  TIM4_TimingDelay = _ms;

  // Interval = 8us*125 = 1ms
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 124);
  TIM4_PrescalerConfig(TIM4_PRESCALER_128, TIM4_PSCRELOADMODE_IMMEDIATE);
  TIM4_ARRPreloadConfig(ENABLE);
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  TIM4_Cmd(ENABLE);
  
  while(TIM4_TimingDelay > 0);
}

void Delay10Us(uint8_t _delay) {
  // Interval = 2us*5 = 10us
  TIM4_TimingDelayUs = _delay;
  TIM4_TimeBaseInit(TIM4_PRESCALER_32, 4);
  TIM4_PrescalerConfig(TIM4_PRESCALER_32, TIM4_PSCRELOADMODE_IMMEDIATE);
  TIM4_ARRPreloadConfig(ENABLE);
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  TIM4_Cmd(ENABLE);
  while(TIM4_TimingDelayUs > 0);
}
