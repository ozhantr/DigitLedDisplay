This fork additions/corrections:
* works under Linux Arduino IDE as well
* print negative numbers as well
* optional cleaning space left of printed number
* new [Digit7SegmentMillis.ino](examples/Digit7SegmentMillis/Digit7SegmentMillis.ino) example 
  * 8 digit display overflows after 27.7 hours
  * optimized loop directions for Digit7SegmentMillis example
  * special display for divisor divi>1  
    (the "8." on left, not visible during update)
* new setDecimalPoint() function (numbers keep long)

This is 1fps animation generated from Raspberry v1 camera 640x64@665fps raspiraw video.  
Demonstrates that it takes less than 3/665=4.5ms to update the 8 positions in led:  
![led.anim.gif](led.anim.gif)

This is 1fps animation generated from different Raspberry v1 camera 640x64@665fps raspiraw video.  
Demonstrates the changed default for Digit7SegmentMillis example, now 1/100th seconds precision with decimal point. Every 6th or 7th frame display gets updated, valid display with "8." left complete: 
![led2.anim.gif](led2.anim.gif)

This is 1fps animation generated from Raspberry v1 camera 640x480@90fps global external shutter video.
The Raspberry [hardware camera sync pulses](https://github.com/Hermann-SW/Raspberry_v1_camera_global_external_shutter#hardware-camera-sync-pulses) are connected to Arduino "sync" pin in new example [Digit7SegmentMillisSync.ino](examples/Digit7SegmentMillisSync/Digit7SegmentMillisSync.ino).
The digits get printed at begin of next v1 camera frame, and cleared after few microseconds:  
![tube.camera_sync.global_external_shutter.anim.gif](tube.camera_sync.global_external_shutter.anim.gif)


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
