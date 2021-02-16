#include "stm32f4xx.h"

int n = 0;
int main()
{
	void initClock();
	void initI2c();
	
	while(1)
	{
		
	}
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;
	GPIOC->ODR ^= GPIO_ODR_ODR_13;
	n++;
}
