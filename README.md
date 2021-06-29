
# CandleLight.ino
Simulates a candlelight/flame effect while brightness is smoothly raised and smoothly *or* rapidly reduced. Thus, even if the sketch is still simple, it is a little bit more complex than the very easy candlelight sketches.

https://github.com/etkaar/CandleLight/blob/main/CandleLight.ino

#### Requirements

- ATtiny85 microcontroller (or similar); see [comparison chart](https://en.wikipedia.org/wiki/ATtiny_microcontroller_comparison_chart).
- Arduino IDE with [ATTinyCore](https://github.com/SpenceKonde/ATTinyCore) by Spence Conde.
  - You can add it by setting "http://drazzy.com/package_drazzy.com_index.json" in File > Preferences > Additional Board Manager URLs, and then Tools > Board > Boards Manager > ATTinyCore > Install.
- A programmer for the microcontroller. You can use an Arduino Uno, ELEGOO UNO (or similar).

#### Settings
- Set your ATtiny on 1 MHz (burn bootloader before uploading the sketch).

#### Real Life Example

See: https://www.youtube.com/watch?v=NNBb8YCEBaA

[![LED Candlelight Effect Example using ATtiny85](https://img.youtube.com/vi/i-p4kunlImk/maxresdefault.jpg)](https://www.youtube.com/watch?v=NNBb8YCEBaA)

