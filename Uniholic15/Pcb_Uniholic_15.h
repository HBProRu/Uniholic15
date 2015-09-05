
//���� 1-Wire ��� ������� ����������� DS18B20
#define ONE_WIRE_BUS 11

//������
#define BUTTON_UP = A2
#define BUTTON_DOWN = A3
#define BUTTON_START = A0
#define BUTTON_ENTER = A1

//LCD
#if LCD_TYPE_CONNECT == 1

//����� RS, E, DB4, DB5, DB6, DB7
#define OUTPUT_LCD_RS = 2
#define OUTPUT_LCD_E = 3
#define OUTPUT_LCD_DB4 = 4
#define OUTPUT_LCD_DB5 = 5
#define OUTPUT_LCD_DB6 = 6
#define OUTPUT_LCD_DB7 = 7

#elif LCD_TYPE_CONNECT == 2 

//����� I2C
#define I2C_LCD_ADDRESS 0x27

//���-�� �������� � ������
#if LCD_CHARS_ROWS == 1

#define I2C_LCD_CHARS = 16
#define I2C_LCD_ROWS = 2

#elif  LCD_CHARS_ROWS == 2

#define I2C_LCD_CHARS = 20
#define I2C_LCD_ROWS = 4

#endif

#endif



//�����
#define OUTPUT_PUMP = 8

//���
#define OUTPUT_HEAT_1 = 9

//�������
#define OUTPUT_BUZZER = 10