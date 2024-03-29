#ifndef __DEVICE_MODE_H
#define __DEVICE_MODE_H

#include "stm32f4xx.h"

int getAdcData(void);
int get_b1(void);
int get_b2(void);
int get_b3(void);
int get_b4(void);

int getTimerTimeSetting(void);
int getDutyCycleSetting(void);
int getTimerTime(void);
int getDelayTimeSetting(void);

void deviceModeHandler(uint32_t bdeviceMode);
	
typedef enum _DEVICE_MODE
{
	ON = 1,
	OFF = 2,
	SETTINGS = 3
} DEVICE_MODE;

extern uint32_t deviceMode;
extern uint32_t impulseMode;
extern uint32_t timerMode;

#endif /* __DEVICE_MODE_H */