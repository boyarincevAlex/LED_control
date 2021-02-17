#include "display mode.h"
#include "LCD1602 Driver.h"
#include "device mode.h"

char* STRING;
char DATA1[4];
char* word = "FA";

void displayModeHandler(uint32_t displayMode)
{
		switch (displayMode)
		{
		case MAIN:
		{
			sendLcdStringToPosition(1,5, "mA");
			sendCurrentDataToDisplay();
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

void sendCurrentDataToDisplay(void)
{
			convertAdcCurrentDataToDisplay();
			sendLcdStringToPosition(1,1, STRING);
//		sendLcdCommand(LCD_ADDR, 0b10000000);
//		sendLcdData(LCD_ADDR, DATA1[0]);
//		sendLcdData(LCD_ADDR, DATA1[1]);
//		sendLcdData(LCD_ADDR, DATA1[2]);
//		sendLcdData(LCD_ADDR, DATA1[3]);
//		sendLcdData(LCD_ADDR, DATA1[4]);
//		sendLcdData(LCD_ADDR, DATA1[5]);

}

void convertAdcCurrentDataToDisplay(void)
{
		//char DATA1[4];
		int DATA_ADC;
		DATA_ADC = getAdcCurrentData();
		DATA1[0] = DATA_ADC/100 + 0x30;
		DATA1[1] = DATA_ADC/10 % 10 + 0x30;
		DATA1[2] = 0x2E;
		DATA1[3] = DATA_ADC % 10 + 0x30;
		STRING = &DATA1[0];
		*(STRING+4) = 0;
}