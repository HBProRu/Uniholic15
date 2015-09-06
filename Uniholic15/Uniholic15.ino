//Настройки отладочного режима
#define DEBUG


//Тип используемой платы
// 1 Uniholic v1.5
#define PCB_TYPE 1

//Способ подключения LCD экрана
// 1 - 
// 2 - по I2C
#define LCD_TYPE_CONNECT 1

//Кол-во символов и строк экрана
// 1 - 16x2
// 2 - 20x4
#define LCD_CHARS_ROWS 1

//Отображаемый язык
// 1 - Русский
// 2 - English
#define LANGUAGE 1

//Динамик
// 0 - отстутствует
// 1 - пассивный
// 2 - активный
#define BUZZER 1

//Точность измерения температуры
#define TEMPERATURE_PRECISION 12



#include "Debug.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "Button.h"
#include "Functions.h"
#include "Setting.h"
#include "PID.h"
#include "Recipe.h"


#if PCB_TYPE == 1
#include "Pcb_Uniholic_15.h"
//#elif PCBType == 2 
//#include "Pcb_Brauduino_DanielXan.h"
#endif



// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature ds(&oneWire);




Button btnUP = Button(BUTTON_UP, BUTTON_PULLDOWN,true,DEBOUNCE_INTERVAL);
Button btnDOWN = Button(BUTTON_DOWN, BUTTON_PULLDOWN, true, DEBOUNCE_INTERVAL);
Button btnSTART = Button(BUTTON_START, BUTTON_PULLDOWN, true, DEBOUNCE_INTERVAL);
Button btnENTER = Button(BUTTON_ENTER, BUTTON_PULLDOWN, true, DEBOUNCE_INTERVAL);


void onPress(Button& b) {
	DebugPrint("onPress: ");
	DebugPrintln(b._pin);
	digitalWrite(OUTPUT_PUMP, HIGH);
}

void onRelease(Button& b) {
	DebugPrint("onRelease: ");
	DebugPrintln(b._pin);
	digitalWrite(OUTPUT_PUMP, LOW);
}

void onHold(Button& b) {
	DebugPrint("Held for at least 1 second: ");
	DebugPrintln(b._pin);
}




void SetRecipe(Recipe recipe) {
	recipe.name = "Hoegaarden";
	recipe.mashin = 45;
	recipe.step[0] = (STEP) { 45, 10 };
	recipe.step[1] = (STEP) { 60, 5 };
	recipe.step[2] = (STEP) { 66, 30 };
	recipe.step[3] = (STEP) { 72, 20 };
	recipe.step[4] = (STEP) { 75, 20 };

	recipe.hop[0] = (HOP) { 60 };
	recipe.hop[1] = (HOP) { 10 };
	recipe.hop[2] = (HOP) { 5 };
	recipe.boil = 90;
}

void dbg_Recipe(Recipe recipe) {
	DebugMills(); DebugPrintln("Start dbg_Recipe");
	DebugPrint("Name: ");
	DebugPrintln(recipe.name);
	DebugPrint("MashIn: ");
	DebugPrintln(recipe.mashin);
	DebugPrintln("Mashing:");
	for (byte i = 0; i < (sizeof(recipe.step) / sizeof(STEP)); i++)
	{
		DebugPrint("Step ");
		DebugPrint(i);
		DebugPrint(" - temp: ");
		DebugPrint(recipe.step[i].temp);
		DebugPrint(" time: ");
		DebugPrintln(recipe.step[i].time);
	}
	DebugPrintln("Hops:");
	for (byte i = 0; i < (sizeof(recipe.hop) / sizeof(HOP)); i++)
	{
		DebugPrint("Hop ");
		DebugPrint(i);
		DebugPrint(" time before boil: ");
		DebugPrintln(recipe.hop[i].time);
	}
	DebugPrint("Boil: ");
	DebugPrintln(recipe.boil);
	DebugMills(); DebugPrintln("End dbg_Recipe");
}



void setup() {

	DebugInit(115200);
	DebugMills();
	DebugPrintln("Starting Uniholic");


	//Инициализируем выходы
	pinMode(OUTPUT_HEAT_1, OUTPUT);
	pinMode(OUTPUT_PUMP, OUTPUT);
	pinMode(OUTPUT_BUZZER, OUTPUT);

	//Инициализируем датчики температуры
	ds.begin();

	DebugMills();
	DebugPrint("Count found OneWire device: ");
	DebugPrintDEC(ds.getDeviceCount());
	DebugPrintln();

	//Устанавливаем разрешение измерения
	ds.setResolution(TEMPERATURE_PRECISION);
	//Выбираем асинхронный режим измерения
	ds.setWaitForConversion(false);

	// Assign callback functions
	//btnUP.pressHandler(onPress);
	//btnUP.releaseHandler(onRelease);
	//btnUP.holdHandler(onHold, 1000); // must be held for at least 1000 ms to trigger



	DebugMills();
	DebugPrintln("Loading Uniholic completed");
}


void loop() {

	ds.requestTemperatures();
	unsigned short delayInMillis = 750 / (1 << (12 - TEMPERATURE_PRECISION));
	delay(delayInMillis);
	DebugMills();
	DebugPrintln(ds.getTempCByIndex(0));
	
	btnUP.process();



}