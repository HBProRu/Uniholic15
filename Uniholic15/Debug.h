// Debug.h

#ifdef DEBUG
#define DebugInit(speed) Serial.begin(speed);
#define Debug(message) {Serial.print(message);}
#define Debugln(message) {Serial.println(message);}


#else
#define DebugInit(speed) {}

#define Debug(message) {}
#define Debugln(message) {}
//
#endif