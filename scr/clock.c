#include "stm32f4xx.h"
#include "clock.h"


void Clock_init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | 
									RCC_AHB1ENR_GPIOBEN | 
									RCC_AHB1ENR_GPIOCEN ;
									
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN | 
									RCC_APB1ENR_TIM5EN | 
									RCC_APB1ENR_TIM3EN;
	
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN  |
									RCC_APB2ENR_SYSCFGEN;
}