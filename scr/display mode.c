#include "display mode.h"
#include "LCD1602 Driver.h"
#include "device mode.h"

char* STRING;
char DATA1[4];
int but1;
int but2;
int but3;
int but4;

void displayModeHandler(uint32_t displayMode)
{
		switch (displayMode)
		{
		case MAIN:
		{
//			but1 = get_b1();
//			but2 = get_b2();
//			but3 = get_b3();
//			but4 = get_b4();
//			sendLcdStringToPosition(1,1, "b1:");
//			sendLcdStringToPosition(1,8, "b2:");
//			sendLcdStringToPosition(2,1, "b3:");
//			sendLcdStringToPosition(2,8, "b4:");
			
			sendLcdStringToPosition(1,5, "mA");
			sendCurrentDataToDisplay(1,1);
			
//			sendIntData3ToDisplay(1,4, but1);
//			sendIntData3ToDisplay(1,11, but2);
//			sendIntData3ToDisplay(2,4, but3);
//			sendIntData3ToDisplay(2,11, but4);
			break;
		}
		
		case INFORMATION:
		{
			sendLcdStringToPosition(1,1, "Timer:");
			if (bTimerMode == ENABLE )
				sendLcdStringToPosition(1,7, "ON ");
			else sendLcdStringToPosition(1,7, "OFF");
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

void sendCurrentDataToDisplay(int string, int column)
{
			convertAdcCurrentDataToDisplay();
			sendLcdStringToPosition(string, column, STRING);
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
		//DATA_ADC = get_m();
		DATA1[0] = DATA_ADC/100 + 0x30;
		DATA1[1] = DATA_ADC/10 % 10 + 0x30;
		DATA1[2] = 0x2E;
		DATA1[3] = DATA_ADC % 10 + 0x30;
		STRING = &DATA1[0];
		*(STRING+4) = 0;
}


