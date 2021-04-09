#include "stm32f4xx.h"
#include "device mode.h"
#include "LCD1602 Driver.h"
#include "display mode.h"

int DATA_ADC;
int DATA_AVR;
int nConversationForAverage = 16;
int nCountAdc;
int adcData;

int b1;
int b2;
int b3;
int b4;
int nTimerTime =1;
int setTimerTime = 10;
int setDutyCycle = 50;
int setDelayTime = 10;

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
				if (displayMode == INFORMATION)
					//Supply Voltage = (3320 * DATA_AVR / 4095)*((R2+R1)/R2) R2=1kOm R1=10kOm
					adcData = 365 * DATA_AVR / 4095;
				else adcData = 3320 * DATA_AVR / 4218;
				DATA_ADC = 0;
				nCountAdc =0;
			}
		}
		
		ADC1->SR=0;
}	

void TIM5_IRQHandler(void)
{
	TIM5->SR &= ~TIM_SR_UIF;
	//GPIOA->ODR ^= GPIO_ODR_ODR_9;
	deviceModeHandler(deviceMode);
	displayModeHandler(displayMode);
	
//	n++;
//	if (n>10)
//	{
//		displayMode = INFORMATION;
//		n = 0;
//	}
}

void TIM4_IRQHandler(void)
{
	TIM4->SR &= ~TIM_SR_UIF;
	if (deviceMode == ON)
	{
		if (timerMode == ENABLE)
			{	
				nTimerTime--;
				if (nTimerTime == 0)
					deviceMode = OFF;
			}
	}
}

//void TIM1_UP_TIM10_IRQHandler(void)
//{
//	TIM1->SR &= ~TIM_SR_UIF;
//	TIM1->CCR2 = 0;
//	TIM1->CR1 &= ~TIM_CR1_CEN;
//	TIM1->CNT = 0;
//	
//	TIM1->CCR3 = 0;
//	deviceMode = OFF;	
//}

void deviceModeHandler(uint32_t bdeviceMode)
{
	switch (bdeviceMode)
	{
		case ON:
		{
//			if (timerMode == ENABLE)
//			{	
//				nTimerTime--;
//				if (nTimerTime == 0)
//					deviceMode = OFF;
//			}
			
			break;	
		}
		case OFF:
		{			
			TIM1->CCR2 = 0;
			TIM1->CCR3 = 0;
			TIM1->CNT = 0;
			TIM1->CR1 &= ~TIM_CR1_CEN;
			break;
		}
		
		case SETTINGS:
		{
			TIM1->CCR2 = 0;
			TIM1->CCR3 = 0;
			TIM1->CNT = 0;
			TIM1->CR1 &= ~TIM_CR1_CEN;
			break;
		}
		
		default:
		{	
			break;
		}
	}
}


void EXTI3_IRQHandler() //Button 4
	{
		//Delay(20);
		if ((GPIOB->IDR & GPIO_IDR_IDR_3) == RESET)
		{
			EXTI->PR = EXTI_PR_PR3;
			EXTI->PR;
			GPIOC->ODR ^= GPIO_ODR_ODR_13;
			b4++;
			clearLcd();
			
			uint32_t currentDeviceMode = deviceMode;
			uint32_t currentDisplayMode = displayMode;
			
//			switch (currentDeviceMode)
//			{
//				case ON:
//				{
//					//deviceMode = OFF;
//					break;
//				}
//				case OFF:
//				{
//					//if (displayMode == MAIN)
//					//	deviceMode = ON;
//					break;
//				}
//				case SETTINGS:
//				{
//					//deviceMode = OFF;
//					break;
//				}
//				default: 
//				{
//					//deviceMode = OFF;
//					break;
//				}
//			}
			
			switch (currentDisplayMode)
			{
				case MAIN:
				{
					if (currentDeviceMode == ON)
						deviceMode = SETTINGS;
					
					displayMode = SETTING_TIMER1;
					break;
				}
				case INFORMATION:
				{
					//displayMode = SETTING_TIMER1;
					break;
				}
				case SETTING_TIMER1:
				{
					if (timerMode == ENABLE)
							displayMode = SETTING_TIMER2;
					else displayMode = SETTING_IMPULSE1;
					break;
				}
				case SETTING_TIMER2:
				{
					nTimerTime = setTimerTime;
//					if (setTimerTime == 0)
//						TIM1->CR1 |= TIM_CR1_OPM;
//					else TIM1->CR1 &= ~TIM_CR1_OPM;
					
					displayMode = SETTING_IMPULSE1;
					break;
				}
				
				case SETTING_IMPULSE1:
				{
					if (impulseMode == ENABLE)
							displayMode = SETTING_IMPULSE2;
					else displayMode = MAIN;
					break;
				}
				
				case SETTING_IMPULSE2:
				{
					displayMode = SETTING_IMPULSE3;
					break;
				}
				
				case SETTING_IMPULSE3:
				{
					displayMode = SETTING_IMPULSE4;
					break;
				}
				
				case SETTING_IMPULSE4:
				{
					displayMode = MAIN;
					break;
				}
				
				default:
				{
					displayMode = MAIN;
					break;
				}
			}
//			
//			
//			if (displayMode == MAIN)
//			{
//				displayMode = SETTING_TIMER1;
//			}
//			else if (displayMode == SETTING_TIMER1)
//			{
//				displayMode = SETTING_TIMER2;
//			}
//			else displayMode = MAIN;
			
		}
		else EXTI->PR = EXTI_PR_PR3;
	}

void EXTI4_IRQHandler() //Button 1
	{
		Delay(20);
		if ((GPIOB->IDR & GPIO_IDR_IDR_4) == RESET)
		{
			EXTI->PR = EXTI_PR_PR4;
			EXTI->PR;
			GPIOC->ODR ^= GPIO_ODR_ODR_13;
			b1++;
			uint32_t currentDeviceMode = deviceMode;
			uint32_t currentDisplayMode = displayMode;
			
			switch (currentDeviceMode)
			{
				case ON:
				{
					deviceMode = OFF;
					TIM1->CR1 &= ~TIM_CR1_CEN;
					TIM1->CCR2 = 0;
					TIM1->CCR3 = 0;
					TIM1->CNT = 0;
					
					break;
				}
				case OFF:
				{
					if (timerMode == ENABLE)
					{
						if (nTimerTime == 0)
						{
							deviceMode = OFF;
						}
						else
						{
							if (displayMode == MAIN)
							{
								deviceMode = ON;
								if (impulseMode == DISABLE)
								{
									TIM1->CCR2 = 1000;
									TIM1->CCR3 = 1000;
								}
								else 
								{
									TIM1->CCR2 = setDutyCycle;
									TIM1->CCR3 = setDelayTime + setDutyCycle;
								}
								TIM1->CR1 |= TIM_CR1_CEN;
							}
						}
					}
					else
					{
						if (displayMode == MAIN)
						{
							deviceMode = ON;
							if (impulseMode == DISABLE)
							{
								TIM1->CCR2 = 1000;
								TIM1->CCR3 = 1000;
							}
							else 
							{
								TIM1->CCR2 = setDutyCycle;
								TIM1->CCR3 = setDelayTime + setDutyCycle;
							}
							TIM1->CR1 |= TIM_CR1_CEN;
						}
					}
					
					
					break;
				}
				case SETTINGS:
				{
					deviceMode = OFF;
					break;
				}
				default: 
				{
					deviceMode = OFF;
					break;
				}
			}
			
			switch (currentDisplayMode)
			{
				case MAIN:
				{
					displayMode = MAIN;
					break;
				}
				case INFORMATION:
				{
					//clearLcd();
					//displayMode = MAIN;
					break;
				}
				case SETTING_TIMER1:
				{
					clearLcd();
					displayMode = MAIN;
					break;
				}
				case SETTING_TIMER2:
				{
					clearLcd();
					displayMode = MAIN;
					break;
				}
				
				case SETTING_IMPULSE1:
				{
					clearLcd();
					displayMode = MAIN;
					break;
				}
				
				case SETTING_IMPULSE2:
				{
					clearLcd();
					displayMode = MAIN;
					break;
				}
				
				case SETTING_IMPULSE3:
				{
					clearLcd();
					displayMode = MAIN;
					break;
				}
				
				case SETTING_IMPULSE4:
				{
					clearLcd();
					displayMode = MAIN;
					break;
				}
				
				default:
				{
					clearLcd();
					displayMode = MAIN;
					break;
				}
			}
		}
		else EXTI->PR = EXTI_PR_PR4;
	}

void EXTI9_5_IRQHandler() //Button 3 and 2
	{
		//int count;
		
		//Delay(20);
		
		if ((GPIOB->IDR & GPIO_IDR_IDR_6) == RESET)
		{
			EXTI->PR = EXTI_PR_PR6;
			EXTI->PR;
			GPIOC->ODR ^= GPIO_ODR_ODR_13;
			
			uint32_t currentDeviceMode = deviceMode;
			uint32_t currentDisplayMode = displayMode;

			switch (currentDisplayMode)
			{
				case MAIN:
				{				
					adcData = 0;
					DATA_ADC = 0;
					nCountAdc = 0;
					TIM3->PSC = 6250-1;
					ADC1->SMPR2 = ADC_SMPR2_SMP6_0;
					ADC1->SQR3 = 0x00000006; 
					clearLcd();
					displayMode = INFORMATION;
					Delay(20);
					break;
				}
				case INFORMATION:
				{
					DATA_ADC = 0;
					nCountAdc = 0;
					TIM3->PSC = 1000-1;
					ADC1->SMPR2 = ADC_SMPR2_SMP8_0;
					ADC1->SQR3 = 0x00000008; 
					clearLcd();
					displayMode = MAIN;
					Delay(20);
					break;
				}
				case SETTING_TIMER1:
				{
					if 	(timerMode == ENABLE)
							timerMode = DISABLE;
					else timerMode = ENABLE;
					break;
				}
				case SETTING_TIMER2:
				{
					setTimerTime+=10;
					break;
				}
				
				case SETTING_IMPULSE1:
				{
					if 	(impulseMode == ENABLE)
							impulseMode = DISABLE;
					else impulseMode = ENABLE;
					break;
				}
				
				case SETTING_IMPULSE2:
				{
					TIM1->PSC += 250;
					break;
				}
				
				case SETTING_IMPULSE3:
				{
					if (setDutyCycle == 1000)
						setDutyCycle = 1000;
					else setDutyCycle += 10;
					
					break;
				}
				
				case SETTING_IMPULSE4:
				{
					if (setDelayTime == (TIM1->ARR - setDutyCycle))
						setDelayTime = TIM1->ARR - setDutyCycle;
					else setDelayTime += 1;
					
					break;
				}
				
				default:
				{
					//displayMode = MAIN;
					break;
				}
			}				
			//}
			b2++;
			
    }
		
		else EXTI->PR = EXTI_PR_PR6;
		
		if ((GPIOB->IDR & GPIO_IDR_IDR_5) == RESET)
		{
			EXTI->PR = EXTI_PR_PR5;
			EXTI->PR;
			
			uint32_t currentDeviceMode = deviceMode;
			uint32_t currentDisplayMode = displayMode;

			switch (currentDisplayMode)
			{
				case MAIN:
				{
					if (timerMode == ENABLE)
						nTimerTime = setTimerTime;
					break;
				}
				case INFORMATION:
				{
					//clearLcd();
					//displayMode = MAIN;
					break;
				}
				case SETTING_TIMER1:
				{
					if 	(timerMode == ENABLE)
							timerMode = DISABLE;
					else timerMode = ENABLE;
					break;
				}
				case SETTING_TIMER2:
				{
					if (setTimerTime == 0)
						setTimerTime = 0;
					else setTimerTime-=10;
					break;
				}
				
				case SETTING_IMPULSE1:
				{
					if 	(impulseMode == ENABLE)
							impulseMode = DISABLE;
					else impulseMode = ENABLE;
					break;
				}
				
				case SETTING_IMPULSE2:
				{
					if (TIM1->PSC == (250-1))
						TIM1->PSC = 250-1;
					else TIM1->PSC -= 250;
					break;
				}
				
				case SETTING_IMPULSE3:
				{
					if (setDutyCycle == 10)
						setDutyCycle = 10;
					else setDutyCycle -= 10;//displayMode = MAIN;
					break;
				}
				
				case SETTING_IMPULSE4:
				{
					if (setDelayTime == 0)
						setDelayTime = 0;
					else setDelayTime -= 1;
					
					break;
				}
				
				default:
				{
					//displayMode = MAIN;
					break;
				}
			}
			
			
			GPIOC->ODR ^= GPIO_ODR_ODR_13;
			b3++;
			//}
		}
		else EXTI->PR = EXTI_PR_PR5;
		//b2++;
		//EXTI->PR |= EXTI_PR_PR5;
		//EXTI->PR |= EXTI_PR_PR6;
	}

	

int getAdcData(void)
{
	return adcData;
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

int getTimerTimeSetting(void)
{
	return setTimerTime;
}

int getTimerTime(void)
{
	return nTimerTime;
}

int getDutyCycleSetting(void)
{
	return setDutyCycle;
}

int getDelayTimeSetting(void)
{
	return setDelayTime;
}
