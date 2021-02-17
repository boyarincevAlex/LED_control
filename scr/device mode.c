#include "stm32f4xx.h"
#include "device mode.h"

void ADC_IRQHandler(void)
{
	  //DATA_AVR = 0;
//		if(ADC1->SR & ADC_SR_EOC)
//		{
//      DATA_ADC =ADC1->DR;
//		
//	
//		//DATA_AVR += ADC1->DR;
//		//DATA_ADC =  DATA_AVR/16;
//		
//		DATA_ADC = 3320 * DATA_ADC / 4218/*4095*/;
//		DATA1[0] = DATA_ADC/100 + 0x30;
//		DATA1[1] = DATA_ADC/10 % 10 + 0x30;
//		DATA1[2] = 0x2E;
//		DATA1[3] = DATA_ADC % 10 + 0x30;
//		DATA1[4] = 0x6D;
//		DATA1[5] = 0x41;
//		GPIOC->ODR ^= GPIO_ODR_ODR_13;
//   }
		ADC1->SR=0;
}	

