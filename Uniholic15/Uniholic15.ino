//#define DEBUG
//
//#ifdef DEBUG
//#define DebugInit(speed) Serial.begin(speed);
//#define Debug(message, code) {Serial.print(message); Serial.println(code);}
//#define Debug(message) {Serial.print(message);}
////#define Debug(message, code) {Serial.print(message); Serial.println(code);}
//#else
//#define DebugInit(speed) {}
//#define Debug(message, code) {}
//#define Debug(message) {}
////
//#endif


#include "OneWire.h"
#include "DallasTemperature.h"
#include "Recipe.h"

Recipe r1 = Recipe();

void setup() {
	
	//DebugInit(115200);
	Serial.begin(115200);

	r1.name = "Hoegaarden";
	r1.mashin = 45;
	r1.step[0] = { 45, 10 };
	r1.step[1] = { 60, 5 };
	r1.step[2] = { 66, 30 };
	r1.step[3] = { 72, 20 };
	r1.step[4] = { 75, 20 };

	r1.hop[0] = { 60 };
	r1.hop[1] = { 10 };
	r1.hop[2] = { 5 };

	r1.boil = 90;

}


void loop() {

	Serial.print("Name: ");
	Serial.println(r1.name);
	Serial.print("MashIn: ");
	Serial.println(r1.mashin);
	Serial.println("Mashing:");
	for (byte i = 0; i < (sizeof(r1.step) / sizeof(STEP)); i++)
	{
		Serial.print("Step ");
		Serial.print(i);
		Serial.print(" - temp: ");
		Serial.print(r1.step[i].temp);
		Serial.print(" time: ");
		Serial.println(r1.step[i].time);
	}
	Serial.println("Hops:");
	for (byte i = 0; i < (sizeof(r1.hop) / sizeof(HOP)); i++)
	{
		Serial.print("Hop ");
		Serial.print(i);
		Serial.print(" time before boil: ");
		Serial.println(r1.hop[i].time);
	}
	Serial.print("Boil: ");
	Serial.println(r1.boil);
	Serial.println("---------------------------------------");

	delay(5000);

	r1.mashin()

}
