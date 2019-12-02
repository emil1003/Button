#ifndef Button_h
#define Button_h

enum states {NONE, PRESS, LONG_PRESS};

class Button {
	private:
		bool _pressed = false;
		bool _longPress = false;
		int _pin = 0;
		unsigned long _pressTime = 0;
		long _longPressThreshold = 2000L;
		bool _block = false;

		bool _pressP;
		bool _longPressP;
	public:
		Button(int pin);
		void check();
		bool isPressed();
		bool isLongPressed();
		states state();
		void setLongPressThreshold(long g);
};

#endif
