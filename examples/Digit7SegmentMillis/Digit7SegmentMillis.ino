/*
   millis() will overflow after 49 days;
   this 8 digit millis() display after 27.7 hours
*/

/* Include DigitLedDisplay Library */
#include "DigitLedDisplay.h"

/* Arduino Pin to Display Pin
   7 to DIN,
   6 to CS,
   5 to CLK */
DigitLedDisplay ld = DigitLedDisplay(7, 6, 5);

unsigned long divi = 10;
unsigned long last = (millis() - 1) / divi;

void setup() {
  /* Set the brightness min:1, max:15 */
  ld.setBright(10);

  /* Set the digit count */
  ld.setDigitLimit(8);

  /* Set the decimal position, 1/100th second */
  ld.setDecimalPos(3);
}

void loop() {
  unsigned long now = millis() / divi;

  /* Print millis()/divi to the display, if changed */
  if (last != now) {
    ld.printDigit(last = now, 0xFF);
    if (divi > 1) {
        ld.write(7, B11111111);
    }
  }
}
