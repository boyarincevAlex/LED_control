#include "stm32f4xx.h"
#include "display mode.h"
#include "device mode.h"

int n = 0;
uint32_t bDisplayMode = MAIN;
int main()
{
	initSystem();
	initLcd();
	
	while(1)
	{
		
	}
}

void TIM5_IRQHandler(void)
{
	TIM5->SR &= ~TIM_SR_UIF;
	GPIOC->ODR ^= GPIO_ODR_ODR_13;
	displayModeHandler(bDisplayMode);
//	n++;
//	if (n>10)
//	{
//		bDisplayMode = INFORMATION;
//		n = 0;
//	}
}


