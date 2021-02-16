#include "stm32f4xx.h"
#include "clock.h"


void initClock(void)
{
	//Frequency HSE - 25 MHz
	RCC->CR |= RCC_CR_HSEON    ;
	
	while (!(RCC->CR & RCC_CR_HSERDY))
	{
	}
		
	RCC->CFGR |=  RCC_CFGR_SW_HSE;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | 
									RCC_AHB1ENR_GPIOBEN | 
									RCC_AHB1ENR_GPIOCEN ;
									
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN | 
									RCC_APB1ENR_TIM5EN | 
									RCC_APB1ENR_TIM3EN;
	
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN  |
									RCC_APB2ENR_SYSCFGEN;

	TIM3->ARR = 25000;
	TIM3->PSC = 1000-1;
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM3_IRQn);
	
	GPIOC->MODER |= GPIO_MODER_MODER13_0;

}
