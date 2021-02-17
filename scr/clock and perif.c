#include "stm32f4xx.h"
#include "clock and perif.h"


void initSystem(void)
{
	initClock();
	initTimer();
	initI2c();
	initAdc();
	
}

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
	
	GPIOC->MODER |= GPIO_MODER_MODER13_0;
	
}

void initI2c(void)
{
	//Don't forget to enable clock in GPIOB and I2C1
	
	GPIOB->MODER |= GPIO_MODER_MODER8_1;  //i2c scl
	GPIOB->MODER |= GPIO_MODER_MODER9_1;	//i2c sda
	
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_1;
	
	GPIOB->OTYPER |= GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9;
	
	GPIOB->AFR[1] |= GPIO_AFRH_AFRH0_2 | GPIO_AFRH_AFRH1_2;
	
	I2C1->CR2 &= ~I2C_CR2_FREQ;
	I2C1->CR2 |= 25;
	
	I2C1->CCR &= ~I2C_CCR_CCR;
	I2C1->CCR |= 250;
	
	I2C1->TRISE = 25;
	I2C1->CR1 |= I2C_CR1_ACK;
	
	I2C1->CR1 |= I2C_CR1_PE;
}	

void initAdc(void)
{
	//Don't forget to enable clock in GPIOA and ADC1
	GPIOA->MODER |= GPIO_MODER_MODER1;
	GPIOB->MODER |= GPIO_MODER_MODER0;
	
	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_EXTEN_0 | ADC_CR2_EXTSEL_3;
	ADC1->SMPR2 = ADC_SMPR2_SMP8_0; 
	NVIC_EnableIRQ(ADC_IRQn);
	ADC1->CR1 = ADC_CR1_EOCIE;
	
	ADC1->SQR1 = 0x00000000;
	ADC1->SQR2 = 0x00000000;
	ADC1->SQR3 = 0x00000008; 
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

void initTimer(void)
{
	//Test Timer - Time 1s 
	TIM5->ARR = 25000;
	TIM5->PSC = 1000-1;
	TIM5->DIER |= TIM_DIER_UIE;
	TIM5->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM5_IRQn);
	
	//ADC Timer - Time 1ms
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->ARR = 2500;
	TIM3->PSC = 1000-1;
	TIM3->CR1 |= TIM_CR1_CEN;
	TIM3->CR2 |= TIM_CR2_MMS_1; 
}