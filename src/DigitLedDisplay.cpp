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

void DigitLedDisplay::clear() {
  for (int i = 1; i <=_digitLimit; i++) {
	write(i, B00000000);
  }
}

void DigitLedDisplay::table(byte address, int val) {
	byte tableValue = pgm_read_byte_near(charTable + val);
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

	int parseInt;
	char str[2];
	for(int i = 0; i < figure.length(); i++) {
		str[0] = figure[i];
		str[1] = '\0';
		parseInt = (int) strtol(str, NULL, 10);
		table(figureLength - i + startDigit, parseInt);
	}
}

void DigitLedDisplay::printDigitAndPeriod(String number) {
	int figureLength = number.length();

	int parseInt;
	char str[2];
	byte buffer[_digitLimit];
	for(int i=0; i<_digitLimit; i++){
		buffer[i] = B00000000;
	}
	int printedDigits = 0;
	for(int i = 0; i < figureLength; i++) {
		if(number[i] != '.'){
			if(number[i] == ' '){
				buffer[printedDigits] = B00000000;
				printedDigits++;
				continue;
			}
			str[0] = number[i];
			str[1] = '\0';
			parseInt = (int) strtol(str, NULL, 10);
			byte tableValue = pgm_read_byte_near(charTable + parseInt);
			buffer[printedDigits] = tableValue;
			printedDigits++;
		}
		else if(printedDigits > 0 && number[i - 1] != '.'){
			buffer[printedDigits - 1] = buffer[printedDigits - 1] | B10000000;
		}
		else {
			buffer[printedDigits] = B10000000;
			printedDigits++;
		}
		Serial.println(printedDigits);
	}
	
	for(int i=0; i < _digitLimit; i++){
		write(i+1, buffer[_digitLimit - i - 1]);
	}
}
