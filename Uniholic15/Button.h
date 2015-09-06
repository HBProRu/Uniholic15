// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#include <inttypes.h>


//Время в мс для подавления дребезга контактов кнопки
#define DEBOUNCE_INTERVAL 50
#define BUTTON_PULLUP HIGH
#define BUTTON_PULLDOWN LOW
#define BUTTON_PULLUP_INTERNAL 2

#define BUTTON_CURRENT 0
#define BUTTON_PREVIOUS 1
#define BUTTON_CHANGED 2

class Button;
typedef void(*buttonEventHandler)(Button&);

class Button
{
public:
	Button(uint8_t pin, uint8_t mode, bool debounceMode = true, int debounceDuration = DEBOUNCE_INTERVAL);

	//Пин подключения кнопки
	uint8_t _pin;

	void pullup(uint8_t mode);
	void pulldown();
	void process();

	bool isPressed(bool proc = true);
	bool wasPressed(bool proc = true);
	bool stateChanged(bool proc = true);
	bool uniquePress();

	void setHoldThreshold(unsigned int holdTime);
	bool held(unsigned int time = 0);
	bool heldFor(unsigned int time);

	void pressHandler(buttonEventHandler handler);
	void releaseHandler(buttonEventHandler handler);
	void clickHandler(buttonEventHandler handler);
	void holdHandler(buttonEventHandler handler, unsigned int holdTime = 0);

	unsigned int holdTime() const;
	const inline unsigned int presses() { return _numberOfPresses; }

	const unsigned int holdTime();
	bool operator==(Button &rhs);

private:
	
	//Cтатус состояния кнопки
	// 0 - отжата
	// 1 - нажата
	uint8_t _state;

	//Подтяжка кнопки
	//BUTTON_PULLUP или BUTTON_PULLDOWN
	unsigned char _mode;

/*
	Button not pressed :

			 VCC
			  |
		 20K | |
	internal | |
	 pull-up |_|
			  |
			  |					_____
	input ––––*––––––o–––––––––o     o––––– GND
					pin       released
							   button

   Button pressed:

		     VCC
		      |    :
	     20K | |   :
	internal | |   :
	 pull-up |_|   :  some current flows
			  |     `- - - - - - - - - ->
			  |
	input ––––*––––––o–––––––––o–––––o––––– GND
				    pin        pushed
							   button
*/



	// longpress duration
	unsigned int _longpress_len;

	//Время начала нажатия
	signed int _pressedStartTime;

	//Кол-во нажатий
	unsigned int _numberOfPresses;

	unsigned int _holdEventThreshold;

	//Флаг триггера удержания
	bool _triggeredHoldEvent;

	buttonEventHandler cb_onPress;
	buttonEventHandler cb_onRelease;
	buttonEventHandler cb_onClick;
	buttonEventHandler cb_onHold;

	//Подавлять дребезг контактов
	bool _debounceMode;
	

	unsigned long _debounceStartTime;
	
	//Время в мс для подавления дребезга контактов
	int _debounceDuration;

};


#endif

