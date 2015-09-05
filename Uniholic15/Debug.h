#ifdef DEBUG



#define DebugInit(speed) Serial.begin(speed);
#define DebugMills() {Serial.print("["); Serial.print(TimeToString(millis())); Serial.print("] ");}
#define DebugPrint(message) {Serial.print(message);}
#define DebugPrintln(message) {Serial.println(message);}


#else
#define DebugInit(speed) {}
#define DebugMills() {}
#define DebugPrint(message) {}
#define DebugPrintln(message) {}

#endif