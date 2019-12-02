//Importer Button biblioteket
#include <Button.h>

//Instantier knappen på pin 8
Button button(8);

//Pin 9 bruges som output
int outPin = 9;

void setup() {
	//Indstil langt tryk til at aktivere efter 500 ms
	button.setLongPressThreshold(500L);
}

void loop() {
	//Kør knappens tjekkode
	button.check();

	//Gør noget baseret på knappens tilstand
	switch (button.state()) {
		case PRESS:
			//Knappen er trykket, tænd outputtet
			digitalWrite(outPin, HIGH);
			break;
		case LONG_PRESS:
			//Knappen er trykket langt, sluk outputtet
			digitalWrite(outPin, LOW);
			break;
	}

	delay(50);
}
