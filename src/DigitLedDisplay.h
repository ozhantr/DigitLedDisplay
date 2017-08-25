#ifndef DigitLedDisplay_h
#define DigitLedDisplay_h

#if defined(__AVR__)
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#endif

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

const static byte charTable [] PROGMEM = {
    B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,B01111111,B01111011
};

const static byte DIGIT_BLANK = B00000000;
const static byte DIGIT_PERIOD = B10000000;
const static byte DIGIT_HYPHEN = B00000001;
const static byte DIGIT_UNDERSCORE = B00001000;


class DigitLedDisplay
{
	private:
		int DIN_PIN;
		int CS_PIN;
		int CLK_PIN;
		int _digitLimit;
		byte* currentDisplayState;
		void table(byte address, int val);
		void setDigitLimit(int limit);
	public:
		DigitLedDisplay(int dinPin, int csPin, int clkPin, int digitLimit);
		void setBright(int brightness);
		void printDigit(long number, byte startDigit = 0);
		void printText(String number, int rightShift = 0, bool clearDisplay = false);
		void write(byte address, byte data);
		void writeDigit(byte address, byte data);
		void clear();
		void on();
		void off();
		~DigitLedDisplay();
};

#endif	//DigitLedDisplay.h
