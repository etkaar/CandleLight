/**
	Copyright (c) 2021 etkaar <https://github.com/etkaar>

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
	OR OTHER DEALINGS IN THE SOFTWARE.
**/

/**
*	CONSTANTS
*/
const byte BREATHING_RANGE_START = 150;
const byte BREATHING_RANGE_END = (255 - 1);

const byte FLICKERING_INTERVALL = 20;

/**
*	ATtiny85 : IC-PIN 3 (PB4)
*/
const byte ARDUINOS_LED_PIN_NUMBER = 4;

void setup() {
	pinMode(ARDUINOS_LED_PIN_NUMBER, OUTPUT);
	
	/**
	*	Initialize with minimum brightness
	*/
	analogWrite(ARDUINOS_LED_PIN_NUMBER, BREATHING_RANGE_START);
}

/**
*	VARIABLES: Global
*/
byte brightness_target = BREATHING_RANGE_START;
byte current_brightness = BREATHING_RANGE_START;

void loop() {
	breathing();
	delay(random(1, 30));
	
	/**
	*	Sometimes: Abrupt continual flickering
	*/
	if (random(0, FLICKERING_INTERVALL) == 0) {
		for (byte i = 0; i < random(0, 12); i++) {
			induce_flickering((current_brightness - random(40, 70)), current_brightness);
		}
	/**
	*	All the time: Some shy flickering
	*/
	} else {
		induce_flickering((current_brightness - 15), current_brightness);
	}
}

/**
*	Brightness is smoothly raised and reduced, the flame 'breathes'
*/
void breathing() {
	/**
	*	Raise brightness; make sure limits are not exceeded
	*/
	if (brightness_target > current_brightness) {
		current_brightness = min(current_brightness + 1, BREATHING_RANGE_END);
		analogWrite(ARDUINOS_LED_PIN_NUMBER, current_brightness);
		
	/**
	*	Target brightness reached
	*/
	} else if (brightness_target == current_brightness) {
		
		/**
		*	Brightness was reduced before to the minimum value;
		*	thus we now need to increase it to a random value.
		*/
		if (brightness_target == BREATHING_RANGE_START) {
			brightness_target = random((BREATHING_RANGE_START + 1), BREATHING_RANGE_END);	
		/**
		*	Brightness was raised before; thus we reduce it
		*	to the minimum value now.
		*/
		} else {
			brightness_target = BREATHING_RANGE_START;
		}
		
	/**
	*	Reduce brightness; make sure limits are not deceeded
	*/
	} else if (brightness_target < current_brightness) {
		current_brightness = max(current_brightness - 1, BREATHING_RANGE_START);
		analogWrite(ARDUINOS_LED_PIN_NUMBER, current_brightness);
	}
}

/**
*	Creates a flickering effect
*/
void induce_flickering(byte min, byte max) {
	analogWrite(ARDUINOS_LED_PIN_NUMBER, min);
	delay(random(100, 150));
	
	analogWrite(ARDUINOS_LED_PIN_NUMBER, max);
	delay(random(100, 150));
}
