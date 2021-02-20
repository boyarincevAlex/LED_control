#ifndef __DEVICE_MODE_H
#define __DEVICE_MODE_H

#include "stm32f4xx.h"

int getAdcCurrentData(void);
int get_b1(void);
int get_b2(void);
int get_b3(void);
int get_b4(void);
	
typedef enum _DEVICE_MODE
{
	ON = 1,
	STOP = 2,
	SETTINGS = 3
} DEVICE_MODE;

extern uint32_t bImpulseMode;
extern uint32_t bTimerMode;

#endif /* __DEVICE_MODE_H */