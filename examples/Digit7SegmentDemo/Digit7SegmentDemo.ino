
/* Include DigitLedDisplay Library */
#include "DigitLedDisplay.h"

/* Arduino Pin to Display Pin
   7 to DIN,
   6 to CS,
   5 to CLK */
DigitLedDisplay ld = DigitLedDisplay(7, 5, 6);

void setup() {

  /* Set the brightness min:1, max:15 */
  ld.setBright(10);

  /* Set the digit count */
  ld.setDigitLimit(8);

}

void loop() {

  /* Prints data to the display */
  ld.printDigit(12345678);
  delay(500);
  ld.clear();

  ld.printDigit(22222222);
  delay(500);
  ld.clear();

  ld.printDigit(44444444);
  delay(500);
  ld.clear();

  for (int i = 0; i < 100; i++) {
    ld.printDigit(i);

    /* Start From Digit 4 */
    ld.printDigit(i, 4);
    delay(50);
  }

  for (int i = 0; i <= 10; i++) {
    /* Display off */
    ld.off();
    delay(150);

    /* Display on */
    ld.on();
    delay(150);
  }

  /* Clear all display value */
  ld.clear();
  delay(500);

  for (long i = 0; i < 100; i++) {
    ld.printDigit(i);
    delay(25);
  }

  for (int i = 0; i <= 20; i++) {
    /* Select Digit 5 and write B01100011 */
    ld.write(5, B01100011);
    delay(200);

    /* Select Digit 5 and write B00011101 */
    ld.write(5, B00011101);
    delay(200);
  }

  /* Clear all display value */
  ld.clear();
  delay(500);

}