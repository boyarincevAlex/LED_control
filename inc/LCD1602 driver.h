
#define PIN_RS    (1 << 0)
#define PIN_EN    (1 << 2)
#define BACKLIGHT (1 << 3)
#define LCD_ADDR (0x27 << 1)

void initLcd(void);
void sendLcdByte(uint8_t addr, uint8_t data, uint8_t flags);
void sendLcdString(uint8_t lcd_addr, char *str);
void sendI2cByte(uint8_t data);
void sendLcdCommand(uint8_t lcd_addr, uint8_t cmd);
void sendLcdData(uint8_t lcd_addr, uint8_t data);
void Delay(uint32_t nCount);
int convertPositionToAdress(uint8_t string, uint8_t column);
void sendLcdStringToPosition(uint8_t string, uint8_t column, char *str);
void sendIntData3ToDisplay(int string, int column, int data);
void sendIntData3PointToDisplay(int string, int column, int data);
void clearLcd(void);


