#include "stm32f4xx.h"
#include "device mode.h"
#include "LCD1602 Driver.h"
#include "display mode.h"

int DATA_ADC;
int DATA_AVR;
int nConversationForAverage = 16;
int nCountAdc;
int adcCurrentData;

int b1;
int b2;
int b3;
int b4;

void ADC_IRQHandler(void)
{
	if(ADC1->SR & ADC_SR_EOC)
		{
			if (nCountAdc < nConversationForAverage)
			{
					DATA_ADC +=ADC1->DR;
					nCountAdc++;
			}
			else
			{
				DATA_AVR = DATA_ADC/nConversationForAverage;
				adcCurrentData = 3320 * DATA_AVR / 4218;
				DATA_ADC = 0;
				nCountAdc =0;
			}
		}
		
		ADC1->SR=0;
}	

/* Device mode */

int getAdcCurrentData(void)
{
	return adcCurrentData;
}

int get_b1(void)
{
	return b1;
}

int get_b2(void)
{
	return b2;
}

int get_b3(void)
{
	return b3;
}

int get_b4(void)
{
	return b4;
}

void EXTI3_IRQHandler() //Button 4
	{
		EXTI->PR = EXTI_PR_PR3;
		EXTI->PR;
		Delay(5);
		GPIOC->ODR ^= GPIO_ODR_ODR_13;
		b4++;
		//sendLcdCommand(LCD_ADDR, 0b00000001);
		//bDisplayMode = INFORMATION;
	}

void EXTI4_IRQHandler() //Button 1
	{
		EXTI->PR = EXTI_PR_PR4;
		EXTI->PR;
		Delay(5);
		GPIOC->ODR ^= GPIO_ODR_ODR_13;
		b1++;
		//sendLcdCommand(LCD_ADDR, 0b00000001);
		//bDisplayMode = MAIN;
	}

void EXTI9_5_IRQHandler() //Button 3 and 2
	{
		if(EXTI->PR & EXTI_PR_PR6)
		{
			EXTI->PR = EXTI_PR_PR6;
			EXTI->PR;
			clearLcd();
			if 	(bDisplayMode == MAIN)
					bDisplayMode = INFORMATION;
			else bDisplayMode = MAIN;
			
			
    }
		if(EXTI->PR & EXTI_PR_PR5)
		{
			EXTI->PR = EXTI_PR_PR5;
			EXTI->PR;
			if (bDisplayMode == INFORMATION)
			{
				if 	(bTimerMode == ENABLE)
							bTimerMode = DISABLE;
				else bTimerMode = ENABLE;
			}
			
			GPIOC->ODR ^= GPIO_ODR_ODR_13;
    }
		Delay(5);
		//b2++;
		//EXTI->PR |= EXTI_PR_PR5;
		//EXTI->PR |= EXTI_PR_PR6;
	}
