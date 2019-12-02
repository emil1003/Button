#include <Arduino.h>
#include "Button.h"

//Initialisér
Button::Button(int pin) {
	//Set pin as input
	pinMode(pin, INPUT);
	_pin = pin;
}

//Tjek knappens tilstand, skal køres hvert loop
void Button::check() {
	//Nulstil knappens tilstand, hvis den var aktiveret
	//Et tryk kan kun bruges i ét loop
	if (_pressP) {
		_pressP = false;
	}
	if (_longPressP) {
		_longPressP = false;
	}

	//Læs om knappen er trykket ned
	if (digitalRead(_pin)) {
		//Knappen blev først trykket ned i dette loop
		if (!_pressed) {
			_pressed = true;
			//Registrer tiden
			_pressTime = millis();
		}
		//Tjek om knappen er holdt nede i mere end _longPressThreshold ms
		if (_pressTime + _longPressThreshold < millis()) {
			_longPress = true;
			_longPressP = true;
		}
	//Ellers hvis knappen er sluppet
	} else {
		//Er knappen ikke blevet trykket langt
		if (!_longPress) {
			//Er knappen trykket og i kortere tid end et langt tryk kræver
			if (_pressed && _pressTime != 0 && _pressTime + _longPressThreshold >= millis()) {
				_pressP = true;
			}
		}
		//Nulstil variabler
		_longPress = false;
		_pressed = false;
		_pressTime = 0;
	}
}

//Returnerer om knappen er trykket
bool Button::isPressed() {
	return _pressP;
}

//Returnerer om knappen er holdt nede i n > _longPressThreshold
bool Button::isLongPressed() {
	return _longPressP;
}

/* Returnerer tilstanden for knappen af typen enum (er deklareret i Button.h)
	PRESS: Knappen er trykket
	LONG_PRESS: Knappen er holdt nede
	NONE: Standard; ingen af betingelserne er opfyldt */
states Button::state() {
	if (_pressP) {
		return PRESS;
	} else if (_longPressP) {
		return LONG_PRESS;
	} else {
		return NONE;
	}
}

//Indstil hvor lang tid i ms der går, før et langt tryk er opfyldt
void Button::setLongPressThreshold(long g) {
	_longPressThreshold = g;
}

