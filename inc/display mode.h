#ifndef __DISPLAY_MODE_H
#define __DISPLAY_MODE_H

#include "stm32f4xx.h"

typedef enum _DISPLAY_MODE
{
	MAIN = 1,
	INFORMATION = 2,
	SETTING_TIMER1 = 3,
	SETTING_TIMER2 = 4,
	SETTING_IMPULSE1 = 5,
	SETTING_IMPULSE2 = 6,
	SETTING_IMPULSE3 = 7,
	SETTING_IMPULSE4 = 8
} DISPLAY_MODE;

void displayModeHandler(uint32_t bDisplayMode);
void sendCurrentDataToDisplay(int string, int column);
void convertAdcDataToDisplay(void);

void convertPeriodDataToDisplay(void);
void sendPeriodDataToDisplay(int string, int column);

void convertDutyCycleDataToDisplay(void);
void sendDutyCycleDataToDisplay(void);

void convertDelayTimeDataToDisplay(void);
void sendDelayTimeDataToDisplay(void);

extern uint32_t displayMode;
extern uint32_t deviceMode;

#endif /* __DISPLAY_MODE_H */