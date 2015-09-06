// 
// 
// 
#include <Arduino.h>
#include "Button.h"

// pin - пин подключения кнопки
// способ подтяжки (BUTTON_PULLUP или BUTTON_PULLDOWN)
Button::Button(uint8_t pin, uint8_t mode, bool debounceMode , int debounceDuration) {
	_pin = pin;
	_state = 0;

	cb_onPress = 0;
	cb_onRelease = 0;
	cb_onClick = 0;
	cb_onHold = 0;

	_numberOfPresses = 0;
	_triggeredHoldEvent = true;

	_debounceMode = debounceMode;
	_debounceDuration = debounceDuration;
	_debounceStartTime = millis();


	pinMode(_pin, INPUT);
	mode == BUTTON_PULLDOWN ? pulldown() : pullup(mode);
	bitWrite(_state, BUTTON_CURRENT, !mode);


}

void Button::pullup(uint8_t mode)
{
	_mode = BUTTON_PULLUP;
	if (mode == BUTTON_PULLUP_INTERNAL)
	{
		digitalWrite(_pin, HIGH);
	}

}

void Button::pulldown(void)
{
	_mode = BUTTON_PULLDOWN;
}


//Нажата ли кнопка
void Button::process(void)
{
	//save the previous value
	bitWrite(_state, BUTTON_PREVIOUS, bitRead(_state, BUTTON_CURRENT));

	//get the current status of the pin
	if (digitalRead(_pin) == _mode)
	{
		//currently the button is not pressed
		bitWrite(_state, BUTTON_CURRENT, false);
	}
	else
	{
		//currently the button is pressed
		bitWrite(_state, BUTTON_CURRENT, true);
	}

	//handle _state changes
	if (bitRead(_state, BUTTON_CURRENT) != bitRead(_state, BUTTON_PREVIOUS))
	{
		signed int interval = millis() - _debounceStartTime;

		if (_debounceMode && interval < _debounceDuration) {
			// not enough time has passed; ignore
			return;
		}
		_debounceStartTime = millis();
		//the state changed to PRESSED
		if (bitRead(_state, BUTTON_CURRENT) == true)
		{
			_numberOfPresses++;
			if (cb_onPress) { cb_onPress(*this); }   //fire the onPress event
			_pressedStartTime = millis();             //start timing
			_triggeredHoldEvent = false;
		}
		else //the state changed to RELEASED
		{
			if (cb_onRelease) { cb_onRelease(*this); } //fire the onRelease event
			if (cb_onClick) { cb_onClick(*this); }   //fire the onClick event AFTER the onRelease
													 //reset states (for timing and for event triggering)
			_pressedStartTime = -1;
		}
		//note that the state changed
		bitWrite(_state, BUTTON_CHANGED, true);
	}
	else
	{
		//note that the state did not change
		bitWrite(_state, BUTTON_CHANGED, false);
		//should we trigger a onHold event?
		if (_pressedStartTime != -1 && !_triggeredHoldEvent)
		{
			if (millis() - _pressedStartTime > _holdEventThreshold)
			{
				if (cb_onHold)
				{
					cb_onHold(*this);
					_triggeredHoldEvent = true;
				}
			}
		}
	}
}

//Возвращает TRUE, если была нажата кнопка
bool Button::isPressed(bool proc)
{
	if (proc) process();
	return bitRead(_state, BUTTON_CURRENT);
}

//Возвращает TRUE, если была нажата кнопка
bool Button::wasPressed(bool proc)
{
	if (proc) process();
	return bitRead(_state, BUTTON_CURRENT);
}

//Возвращает TRUE, если статуc кнопки изменился
bool Button::stateChanged(bool proc)
{
	if (proc) process();
	return bitRead(_state, BUTTON_CHANGED);
}
//Возвращает TRUE, если нажатие одиночное, без последющего удержания
bool Button::uniquePress()
{
	process();
	return (isPressed(false) && stateChanged(false));
}

//Возвращает TRUE, если кнопка удерживается больше указанного времени
bool Button::held(unsigned int time /*=0*/)
{
	process();
	unsigned int threshold = time ? time : _holdEventThreshold; //use holdEventThreshold if time == 0
															   //should we trigger a onHold event?
	if (_pressedStartTime != -1 && !_triggeredHoldEvent)
	{
		if (millis() - _pressedStartTime > threshold)
		{
			_triggeredHoldEvent = true;
			return true;
		}
	}
	return false;
}

/*
|| @description
|| | Polling model for holding, this is true every check after hold time
|| | Check to see if the button has been pressed for time ms
|| #
*/
//Возвращает TRUE, если кнопка удерживается больше указанного времени
bool Button::heldFor(unsigned int time)
{
	if (isPressed())
	{
		if (millis() - _pressedStartTime > time) { return true; }
	}
	return false;
}

//Задать порог времени, после которого кнопка считается удерживаемой
void Button::setHoldThreshold(unsigned int holdTime)
{
	_holdEventThreshold = holdTime;
}

//Указать обрработчик нажатия
void Button::pressHandler(buttonEventHandler handler)
{
	cb_onPress = handler;
}

//Указать обрработчик отпускания
void Button::releaseHandler(buttonEventHandler handler)
{
	cb_onRelease = handler;
}

//Указать обрработчик Click
void Button::clickHandler(buttonEventHandler handler)
{
	cb_onClick = handler;
}

//Указать обрработчик удержания
void Button::holdHandler(buttonEventHandler handler, unsigned int holdTime /*=0*/)
{
	if (holdTime>0) { setHoldThreshold(holdTime); }
	cb_onHold = handler;
}

//Возвращает, сколько удерживается кнопка
const unsigned int Button::holdTime() {
	if (_pressedStartTime != -1)
		return millis() - _pressedStartTime;
	else
		return 0;
}

/*
|| @description
|| | Compare a button object against this
|| #
||
|| @parameter  rhs the Button to compare against this Button
||
|| @return true if they are the same
*/
bool Button::operator==(Button &rhs)
{
	return (this == &rhs);
}