#include "stm32f4xx.h"

typedef enum _DISPLAY_MODE
{
	MAIN = 1,
	INFORMATION = 2,
	SETTING = 3
} DISPLAY_MODE;

void displayModeHandler(uint32_t displayMode);

extern uint32_t bDisplayMode;