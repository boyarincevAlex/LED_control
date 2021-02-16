#include "stm32f4xx.h"
#include "LCD1602 driver.h"

int n = 0;
int main()
{
	initClock();
	initI2c();
	initLcd();
	
	while(1)
	{
		
	}
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;
	GPIOC->ODR ^= GPIO_ODR_ODR_13;
	sendLcdStringToPosition(2,2,"LCD string");
	n++;
}
