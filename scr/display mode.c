#include "display mode.h"
#include "LCD1602 Driver.h"
#include "device mode.h"

char* stringCurrent;
char* srtingPeriod;
char* stringDutyCycle;
char* stringDelayTime;

char dataCurrent[4];
char dataPeriod[4];
int but1;
int but2;
int but3;
int but4;

void displayModeHandler(uint32_t bDisplayMode)
{
		switch (bDisplayMode)
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
//			sendIntData3ToDisplay(1,4, but1);
//			sendIntData3ToDisplay(1,11, but2);
//			sendIntData3ToDisplay(2,4, but3);
//			sendIntData3ToDisplay(2,11, but4);
			
			sendLcdStringToPosition(1,1, "Id=");
			sendLcdStringToPosition(1,8, "mA");
			sendCurrentDataToDisplay(1,4);
			if (timerMode == ENABLE )
			{		
					int t = getTimerTime();
				sendLcdStringToPosition(2,1, "Timer:");
				sendIntData3ToDisplay(2,7, t);
				sendLcdStringToPosition(2,11, "s");
			}
			
			if (deviceMode == ON)
				sendLcdStringToPosition(1,14, "ON ");
			else sendLcdStringToPosition(1,14, "OFF");
			
			break;
		}
		
		case INFORMATION:
		{
			sendLcdStringToPosition(1,1, "E=");
			sendLcdStringToPosition(1,7, "V");
			sendCurrentDataToDisplay(1,3);
			sendLcdStringToPosition(1,10, "Imp:");
			if (impulseMode == ENABLE )
			{
				sendLcdStringToPosition(1,14, "ON ");
				sendLcdStringToPosition(2,1, "T:");
				sendPeriodDataToDisplay(2,3);
				sendLcdStringToPosition(2,7, "ms");
				int d = getDutyCycleSetting()/10;
				sendLcdStringToPosition(2,10, "D:");
				sendIntData3ToDisplay(2,12, d);
				sendLcdStringToPosition(2,15, "%");
				
			}
			else sendLcdStringToPosition(1,14, "OFF");
			
			//but4 = get_b4();
			//but3 = get_b3();
			
			//sendLcdStringToPosition(2,1, "b3:");
			//sendLcdStringToPosition(2,8, "b4:");
			//sendIntData3ToDisplay(2,4, but3);						
			//sendIntData3ToDisplay(2,11, but4);
			
			break;
		}
		
		case SETTING_TIMER1:
		{
			sendLcdStringToPosition(1,1, "Timer:");
			if (timerMode == ENABLE )
				sendLcdStringToPosition(2,1, "ON ");
			else sendLcdStringToPosition(2,1, "OFF");
			
			break;
		}
		
		case SETTING_TIMER2:
		{
			sendLcdStringToPosition(1,1, "Timer time:");
			int t = getTimerTimeSetting();
			sendIntData3ToDisplay(2,1, t);
			sendLcdStringToPosition(2,5, "s");
			break;
		}
		
		case SETTING_IMPULSE1:
		{
			sendLcdStringToPosition(1,1, "Impulse mode:");
			if (impulseMode == ENABLE )
				sendLcdStringToPosition(2,1, "ON ");
			else sendLcdStringToPosition(2,1, "OFF");
			break;
		}	

		case SETTING_IMPULSE2:
		{
			sendLcdStringToPosition(1,1, "Impulse period:");
			sendPeriodDataToDisplay(2,1);
			sendLcdStringToPosition(2,6, "ms");
			break;
		}	
		
		case SETTING_IMPULSE3:
		{
			sendLcdStringToPosition(1,1, "Duty cycle:");
			int dutyCyclePercent = getDutyCycleSetting()/10;
			sendIntData3ToDisplay(2,1, dutyCyclePercent);
			sendLcdStringToPosition(2,4, "%");
			int dutyCycleTime = (TIM1->PSC + 1)*dutyCyclePercent/(25*100);
			sendIntData3ToDisplay(2,11, dutyCycleTime);
			sendLcdStringToPosition(2,15, "ms");
			break;
		}

		case SETTING_IMPULSE4:
		{
			sendLcdStringToPosition(1,1, "Delay time:");
			int delayTimePercent = getDelayTimeSetting();
			sendIntData3PointToDisplay(2,1, delayTimePercent);
			sendLcdStringToPosition(2,5, "%");
			int dutyCycleTime = (TIM1->PSC + 1)*delayTimePercent/(25*100);
			sendIntData3PointToDisplay(2,11, dutyCycleTime);
			sendLcdStringToPosition(2,15, "ms");
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
			convertAdcDataToDisplay();
			sendLcdStringToPosition(string, column, stringCurrent);
//		sendLcdCommand(LCD_ADDR, 0b10000000);
//		sendLcdData(LCD_ADDR, dataCurrent[0]);
//		sendLcdData(LCD_ADDR, dataCurrent[1]);
//		sendLcdData(LCD_ADDR, dataCurrent[2]);
//		sendLcdData(LCD_ADDR, dataCurrent[3]);
//		sendLcdData(LCD_ADDR, dataCurrent[4]);
//		sendLcdData(LCD_ADDR, dataCurrent[5]);

}

void convertAdcDataToDisplay(void)
{
		//char dataCurrent[4];
		int DATA_ADC;
		DATA_ADC = getAdcData();
		//DATA_ADC = get_m();
		dataCurrent[0] = DATA_ADC/100 + 0x30;
		dataCurrent[1] = DATA_ADC/10 % 10 + 0x30;
		dataCurrent[2] = 0x2E;
		dataCurrent[3] = DATA_ADC % 10 + 0x30;
		stringCurrent = &dataCurrent[0];
		*(stringCurrent+4) = 0;
}

void convertPeriodDataToDisplay(void)
{
		int period;
		period = (TIM1->PSC + 1)/25;
		//DATA_ADC = get_m();
		dataPeriod[0] = period/1000 + 0x30;
		dataPeriod[1] = period/100 % 10 + 0x30;
		dataPeriod[2] = period/10 % 10 + 0x30;
		dataPeriod[3] = period % 10 + 0x30;
		srtingPeriod = &dataPeriod[0];
		*(srtingPeriod+4) = 0;
}

void sendPeriodDataToDisplay(int string, int column)
{
		convertPeriodDataToDisplay();
		sendLcdStringToPosition(string, column, srtingPeriod);
}

