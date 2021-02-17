#ifndef __DEVICE_MODE_H
#define __DEVICE_MODE_H

#include "stm32f4xx.h"

int getAdcCurrentData(void);
	
typedef enum _DEVICE_MODE
{
	ON = 1,
	OFF = 2,
	SETTINGS = 3
} DEVICE_MODE;


#endif /* __DEVICE_MODE_H */