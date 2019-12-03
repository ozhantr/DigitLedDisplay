#include "DigitLedDisplay.h"

#define DECODEMODE_ADDR 9
#define BRIGHTNESS_ADDR	10
#define SCANLIMIT_ADDR	11
#define SHUTDOWN_ADDR	12
#define DISPLAYTEST_ADDR 15


DigitLedDisplay::DigitLedDisplay(int dinPin, int csPin, int clkPin) {
	DIN_PIN = dinPin;
	CS_PIN = csPin;
	CLK_PIN = clkPin;
	
	pinMode(DIN_PIN, OUTPUT);
	pinMode(CS_PIN, OUTPUT);
	pinMode(CLK_PIN, OUTPUT);
	digitalWrite(CS_PIN, HIGH);
}

void DigitLedDisplay::setBright(int brightness) {
    if (brightness>=0 && brightness<16)	
        write(BRIGHTNESS_ADDR, brightness);
}

void DigitLedDisplay::setDigitLimit(int limit) {
	_digitLimit = limit;

	write(DISPLAYTEST_ADDR, 0);
	write(SCANLIMIT_ADDR, limit-1);

	// 0: Register Format
	// 255: Code B Font (0xff)
	write(DECODEMODE_ADDR, 0);
	clear();
	write(SHUTDOWN_ADDR, 1);
}

		
void DigitLedDisplay::on() {
	write(SHUTDOWN_ADDR, 0x01);
}

void DigitLedDisplay::off() {
	write(SHUTDOWN_ADDR, 0x00);
}

void DigitLedDisplay::clear(byte start) {
  for (int i = _digitLimit; i >= start; i--) {
	write(i, B00000000);
  }
}

void DigitLedDisplay::table(byte address, int val) {
	byte tableValue;
	tableValue = pgm_read_byte_near(charTable + 1 + val);
	write(address, tableValue);
}

void DigitLedDisplay::write(volatile byte address, volatile byte data) {
	digitalWrite(CS_PIN, LOW);
	shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, address);
	shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, data);
	digitalWrite(CS_PIN, HIGH);
}

void DigitLedDisplay::printDigit(long number, byte startDigit) {
	String figure = String(number);
	int figureLength = figure.length();

        if (startDigit > _digitLimit) {
            startDigit = 0;
            clear(figureLength + 1);
        }

	int parseInt;
	char str[2];
	for(int i = figure.length() - 1; i >=0; i--) {
            if (i==0 && figure[i]=='-') {
                parseInt = -1;
            } else {
		str[0] = figure[i];
		str[1] = '\0';
		parseInt = (int) strtol(str, NULL, 10);
            }
		table(figureLength - i + startDigit, parseInt);
	}
}
