#include "DigitLedDisplay.h"

DigitLedDisplay ld = DigitLedDisplay(5, 6, 7);

// Raspberry Pi camera hardware sync pulse 
int sync=11; 
bool reverse = true;

void setup() {
  pinMode(sync, INPUT);  
  ld.setBright(10);
  ld.setDigitLimit(8);
  ld.setDecimalPos(4);
}

void loop() {
  // wait for frame end
  if (digitalRead(sync)==0) {
    // wait for start of frame
    while (digitalRead(sync)==0) { }

    ld.printDigit(millis());
    delay(1);
    // short display 
    ld.clear(1, reverse); 
    // for global (external) shutter capturing
  }
} 
