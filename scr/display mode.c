#include "display mode.h"
#include "LCD1602 Driver.h"


void displayModeHandler(uint32_t displayMode)
{
		switch (displayMode)
		{
		case MAIN:
		{
			sendLcdStringToPosition(1,2, "test1");
			break;
		}
		
		case INFORMATION:
		{
			sendLcdStringToPosition(2,2, "test2");
			break;
		}
		
		case SETTING:
		{
			break;
		}
	
		default:
		{
			break;
		}
	
	}
}



