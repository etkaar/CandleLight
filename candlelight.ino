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
*	Tested on ATtiny85 on 1 MHz
*/

/**
*	Settings
*/
const byte MIN_BRIGHTNESS = 190;
const byte MAX_BRIGHTNESS = (255 - 1);

const byte FLICKER_INTERVALL = 20;

/**
*	Various
*/
const byte ARDUINOS_LED_PIN_NUMBER = 4;

void setup() {
	pinMode(ARDUINOS_LED_PIN_NUMBER, OUTPUT);
	
	/**
	*	Initialize with minimum brightness
	*/
	analogWrite(ARDUINOS_LED_PIN_NUMBER, MIN_BRIGHTNESS);
}

/**
*	To be altered during runtime
*/
byte brightness_target = MIN_BRIGHTNESS;
byte current_brightness = MIN_BRIGHTNESS;

void loop() {
	byte requested_delay = 0;
	
	/**
	*	Raise brightness; make sure limits are not exceeded
	*/
	if (brightness_target > current_brightness) {
		current_brightness = min(current_brightness + 1, MAX_BRIGHTNESS);
		analogWrite(ARDUINOS_LED_PIN_NUMBER, current_brightness);
		
		requested_delay = random(1, 10);
		
	/**
	*	Target brightness reached
	*/
	} else if (brightness_target == current_brightness) {
		
		/**
		*	Brightness was reduced before to the minimum value;
		*	thus we now need to increase it to a random value.
		*/
		if (brightness_target == MIN_BRIGHTNESS) {
			brightness_target = random((MIN_BRIGHTNESS + 1), MAX_BRIGHTNESS);	
		/**
		*	Brightness was raised before; thus we reduce it
		*	to the minimum value now.
		*/
		} else {
			brightness_target = MIN_BRIGHTNESS;
		}
		
		/**
		*	Increase delay
		*/
		requested_delay = random(30, 150);
		
	/**
	*	Reduce brightness; make sure limits are not deceeded
	*/
	} else if (brightness_target < current_brightness) {
		/**
		*	Normally the brightness is reduced smoothly, but sometimes
		*	we simply want a rapid flickering looking drop.
		*/
		if (random(0, FLICKER_INTERVALL) == 0) {
			current_brightness = MIN_BRIGHTNESS;
		} else {
			current_brightness = max(current_brightness - 1, MIN_BRIGHTNESS);
		}
		
		analogWrite(ARDUINOS_LED_PIN_NUMBER, current_brightness);
		
		requested_delay = random(1, 10);
	}
	
	delay(requested_delay);
}
