DigitLedDisplay
==========
DigitLedDisplay is an [Arduino](http://arduino.cc) library for MAX7219 and MAX7221 8 bit 7-segment digital LED display module drivers.

Install
-------
[Arduino library install guide](https://www.arduino.cc/en/Guide/Libraries)

Or you can copy DigitLedDisplay library to -> arduino\libraries\

-------
*Start From Digit: Default Value Zero*\
`digitLedDisplay.printDigit(1234);`\
![digidled0](https://cloud.githubusercontent.com/assets/3593584/26308379/a9b9fd84-3f01-11e7-924b-f0f810f4d22a.jpg)

*Start From Digit 4*\
`digitLedDisplay.printDigit(1234, 4);`\
![digidled4](https://cloud.githubusercontent.com/assets/3593584/26308387/b0f90c7a-3f01-11e7-93a0-2834827b2145.jpg)

## Quickstart

```c
#include <DigitLedDisplay.h>

// initialize with pin numbers for data, cs, and clock
DigitLedDisplay ld = DigitLedDisplay(7, 6, 5);

void setup() {
  ld.setBright(15); // range is 0-15
  ld.setDigitLimit(8);
}

long i = 12345678;

void loop() {
  ld.printDigit(i++);
  delay(10);
}
```

For additional features see [Digit7SegmentDemo.ino](examples/Digit7SegmentDemo/Digit7SegmentDemo.ino)
