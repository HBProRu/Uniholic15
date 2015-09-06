#if PCB_TYPE == 1
	#include "Pcb_Uniholic_15.h"
//#elif PCBType == 2 
//	#include "Pcb_Brauduino_DanielXan.h"
#endif

//Возвращает время в формате "HH:mm:ss.SSS" из миллисекунд
char * TimeToString(unsigned long t)
{
	static char str[14];
	unsigned short ms = t % 1000;
	unsigned char s = (t/1000) % 60;
	unsigned char m = (t / 1000 / 60) % 60;
	long h = (t / 1000 / 60 / 60);
	sprintf(str, "%02ld:%02d:%02d.%03d", h, m, s, ms);
	return str;
}


void Beep(byte NumBeep, int Period)
{
#if BUZZER == 1
	for (unsigned char i = 0; i < NumBeep; i++)
	{
		for (signed short int k = 0; k < 2400; k++) {
			digitalWrite(OUTPUT_BUZZER, HIGH);
			delayMicroseconds(208);
			digitalWrite(OUTPUT_BUZZER, LOW);
			delayMicroseconds(208);
		}
		delay(Period);
	}
#elif BUZZER == 2
	for (unsigned char i = 0; i < NumBeep; i++) {
		digitalWrite(OUTPUT_BUZZER, HIGH);
		delay(Period);
		digitalWrite(OUTPUT_BUZZER, LOW);
		delay(100);
	}
#endif
}