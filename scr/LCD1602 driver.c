#include "stm32f4xx.h"
#include "LCD1602 Driver.h"




void sendLcdByte(uint8_t addr, uint8_t data, uint8_t flags)
{
	  uint8_t up = data & 0xF0;
    uint8_t lo = (data << 4) & 0xF0;

    uint8_t data_arr[4];
    data_arr[0] = up|flags|BACKLIGHT|PIN_EN;
    data_arr[1] = up|flags|BACKLIGHT;
    data_arr[2] = lo|flags|BACKLIGHT|PIN_EN;
    data_arr[3] = lo|flags|BACKLIGHT;
	
		I2C1->CR1 |= I2C_CR1_START;
		
		while (!(I2C1->SR1 & I2C_SR1_SB))
			{
			}


		I2C1->DR = addr;

		while (!(I2C1->SR1 & I2C_SR1_ADDR))
			{
			}
			
		while ((I2C1->SR1 & I2C_SR1_AF))
		{
		}
		
		(void) I2C1->SR2;	
//		while (!(I2C1->SR1 & I2C_SR1_TXE))
//		{
//		}
		
		sendI2cByte(data_arr[0]);
		sendI2cByte(data_arr[1]);
		sendI2cByte(data_arr[2]);
		sendI2cByte(data_arr[3]);
		
		while (!(I2C1->SR1 & I2C_SR1_BTF))
			{
			}	
		
		I2C1->CR1 |= I2C_CR1_STOP;
		Delay(5);
}
	
void sendLcdString(uint8_t lcd_addr, char *str) 
{
    while(*str) {
        sendLcdData(lcd_addr, (uint8_t)(*str));
        str++;
    }
}

void sendLcdCommand(uint8_t lcd_addr, uint8_t cmd) 
{
    sendLcdByte(lcd_addr, cmd, 0);
}

void sendLcdData(uint8_t lcd_addr, uint8_t data) 
{
    sendLcdByte(lcd_addr, data, PIN_RS);
}

void sendI2cByte(uint8_t data)
{
	while (!(I2C1->SR1 & I2C_SR1_TXE))
		{
		}
	I2C1->DR = data;
		
	while ((I2C1->SR1 & I2C_SR1_AF))
		{
		}

}

void initLcd(void)
{
	sendLcdCommand(LCD_ADDR, 0x0C);
	sendLcdCommand(LCD_ADDR, 0x0C);
	sendLcdCommand(LCD_ADDR, 0x0C);
	sendLcdCommand(LCD_ADDR, 0b00110000);
	sendLcdCommand(LCD_ADDR, 0b00000010);
	sendLcdCommand(LCD_ADDR, 0b00001100);
	sendLcdCommand(LCD_ADDR, 0b00000001);
}

void Delay(uint32_t nCount) 
{
	nCount *= 4000;
	while (nCount != 0)
		nCount--;
}

int convertPositionToAdress(uint8_t string, uint8_t column)
{
	int adress;
	if (string == 1)
		adress = 0b10000000;
	else if (string == 2)
		adress = 0b11000000;
	else adress = 0;
	
	adress = adress + column - 1;
	return adress;
}

void sendLcdStringToPosition(uint8_t string, uint8_t column, char *str)
{
	int adress = convertPositionToAdress(string, column);
	sendLcdCommand(LCD_ADDR, adress);
	sendLcdString(LCD_ADDR, str); 
}
	


void sendIntData3ToDisplay(int string, int column, int data)
{
		int adress = convertPositionToAdress(string, column);
		int DATA1[3];
		DATA1[0] = data/100 + 0x30;
		DATA1[1] = data/10 % 10 + 0x30;
		DATA1[2] = data % 10 + 0x30;
		sendLcdCommand(LCD_ADDR, adress);
		sendLcdData(LCD_ADDR, DATA1[0]);
		sendLcdData(LCD_ADDR, DATA1[1]);
		sendLcdData(LCD_ADDR, DATA1[2]);
}