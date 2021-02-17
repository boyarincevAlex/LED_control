#include "display mode.h"
#include "LCD1602 Driver.h"
#include "device mode.h"

void displayModeHandler(uint32_t displayMode)
{
		switch (displayMode)
		{
		case MAIN:
		{
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
		uint8_t DATA1[6];
		int DATA_ADC;
		DATA_ADC = getAdcCurrentData();
		DATA1[0] = DATA_ADC/100 + 0x30;
		DATA1[1] = DATA_ADC/10 % 10 + 0x30;
		DATA1[2] = 0x2E;
		DATA1[3] = DATA_ADC % 10 + 0x30;
		DATA1[4] = 0x6D;
		DATA1[5] = 0x41;
	
		sendLcdCommand(LCD_ADDR, 0b10000000);
		sendLcdData(LCD_ADDR, DATA1[0]);
		sendLcdData(LCD_ADDR, DATA1[1]);
		sendLcdData(LCD_ADDR, DATA1[2]);
		sendLcdData(LCD_ADDR, DATA1[3]);
		sendLcdData(LCD_ADDR, DATA1[4]);
		sendLcdData(LCD_ADDR, DATA1[5]);

}