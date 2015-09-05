//#define DEBUG

#include "Debug.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "Recipe.h"
#include "Functions.h"


Recipe r1 = Recipe();

void setup() {
	
	DebugInit(115200);
	DebugMills();
	DebugPrintln("Starting Uniholic");

	r1.name = "Hoegaarden";
	r1.mashin = 45;
	r1.step[0] = STEP { 45, 10 };
	r1.step[1] = STEP { 60, 5 };
	r1.step[2] = STEP { 66, 30 };
	r1.step[3] = STEP { 72, 20 };
	r1.step[4] = STEP { 75, 20 };

	r1.hop[0] = HOP { 60 };
	r1.hop[1] = HOP { 10 };
	r1.hop[2] = HOP { 5 };

	r1.boil = 90;

}


void loop() {

	dbg_Recipe(r1);
	delay(200);

}

void dbg_Recipe(Recipe recipe) {
	DebugMills(); DebugPrintln("Start dbg_Recipe");
	DebugPrint("Name: ");
	DebugPrintln(r1.name);
	DebugPrint("MashIn: ");
	DebugPrintln(r1.mashin);
	DebugPrintln("Mashing:");
	for (byte i = 0; i < (sizeof(r1.step) / sizeof(STEP)); i++)
	{
		DebugPrint("Step ");
		DebugPrint(i);
		DebugPrint(" - temp: ");
		DebugPrint(r1.step[i].temp);
		DebugPrint(" time: ");
		DebugPrintln(r1.step[i].time);
	}
	DebugPrintln("Hops:");
	for (byte i = 0; i < (sizeof(r1.hop) / sizeof(HOP)); i++)
	{
		DebugPrint("Hop ");
		DebugPrint(i);
		DebugPrint(" time before boil: ");
		DebugPrintln(r1.hop[i].time);
	}
	DebugPrint("Boil: ");
	DebugPrintln(r1.boil);
	DebugMills(); DebugPrintln("End dbg_Recipe");
}