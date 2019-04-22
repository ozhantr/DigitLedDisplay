#include "DigitLedDisplay.h"

#define DECODEMODE_ADDR 9
#define BRIGHTNESS_ADDR	10
#define SCANLIMIT_ADDR	11
#define SHUTDOWN_ADDR	12
#define DISPLAYTEST_ADDR 15


DigitLedDisplay::DigitLedDisplay(int dinPin, int csPin, int clkPin, int digitLimit) {
	DIN_PIN = dinPin;
	CS_PIN = csPin;
	CLK_PIN = clkPin;
	
	pinMode(DIN_PIN, OUTPUT);
	pinMode(CS_PIN, OUTPUT);
	pinMode(CLK_PIN, OUTPUT);
	digitalWrite(CS_PIN, HIGH);
	
	setDigitLimit(digitLimit);
}

DigitLedDisplay::~DigitLedDisplay(){
	if(currentDisplayState){
		delete[] currentDisplayState;
	}
}

void DigitLedDisplay::setBright(int brightness) {
    if (brightness>=0 && brightness<16)	
        write(BRIGHTNESS_ADDR, brightness);
}

void DigitLedDisplay::setDigitLimit(int limit) {
	_digitLimit = limit;
	currentDisplayState = new byte[_digitLimit];

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
  for (int i = 1; i <= _digitLimit; i++) {
	writeDigit(i, DIGIT_BLANK);
	currentDisplayState[i - 1] = DIGIT_BLANK;
  }
}

void DigitLedDisplay::table(byte address, int val) {
	byte tableValue = pgm_read_byte_near(charTable + val);
	writeDigit(address, tableValue);
}

void DigitLedDisplay::write(volatile byte address, volatile byte data) {
	digitalWrite(CS_PIN, LOW);
	shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, address);
	shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, data);
	digitalWrite(CS_PIN, HIGH);
}

void DigitLedDisplay::writeDigit(volatile byte address, volatile byte data) {
	address = (address % _digitLimit) + 1;
	write(address, data);
	currentDisplayState[address - 1] = data;
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

void DigitLedDisplay::printText(String number, int rightShift, bool clearDisplay) {
	int figureLength = number.length();

	int parseInt;
	char str[2];
	
	byte buffer[_digitLimit];
	for(int i = 0; i < _digitLimit; i++){
		if(clearDisplay){
			buffer[_digitLimit - i - 1] = DIGIT_BLANK;
			continue;
		}
		buffer[_digitLimit - i - 1] = currentDisplayState[i];
	}
	
	int printedDigits = 0;
	int spacesInRow = 0;
	for(int i = 0; i < figureLength; i++) {
		int digitIndex = (printedDigits + rightShift) % _digitLimit;
		if(digitIndex < 0){
			digitIndex = _digitLimit + digitIndex;
		}
		
		if(number[i] != '.'){
			
			if(number[i] == ' '){
				spacesInRow++;
				buffer[digitIndex] = DIGIT_BLANK;
				if(spacesInRow % 2 == 0){
					printedDigits++;
				}
				continue;
			}
			else if(number[i] == '-'){
				buffer[digitIndex] = DIGIT_HYPHEN;
				printedDigits++;
				continue;
			}
			else if(number[i] == '_'){
				buffer[digitIndex] = DIGIT_UNDERSCORE;
				printedDigits++;
				continue;
			}
			
			spacesInRow = 0;
			str[0] = number[i];
			str[1] = '\0';
			parseInt = (int) strtol(str, NULL, 10);
			byte tableValue = pgm_read_byte_near(charTable + parseInt);
			buffer[digitIndex] = tableValue;
			printedDigits++;
		}
		// Add period to previous digit
		else if(printedDigits > 0 && number[i - 1] != ' ' && number[i - 1] != '.'){
			if(digitIndex < 1){
				digitIndex = (printedDigits - 1) % _digitLimit;
			}
			else {
				digitIndex--;
			}
			buffer[digitIndex] = buffer[digitIndex] | DIGIT_PERIOD;
		}
		// Add period alone
		else {
			buffer[digitIndex] = DIGIT_PERIOD;
			printedDigits++;
		}
	}
	
	for(int i = 0; i < _digitLimit; i++){
		writeDigit(i, buffer[_digitLimit - i - 1]);
	}
}
