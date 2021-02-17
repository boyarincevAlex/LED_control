#include "stm32f4xx.h"
#include "device mode.h"

int DATA_ADC;
int DATA_AVR;
int nConversationForAverage = 16;
int nCountAdc;
int adcCurrentData;

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
