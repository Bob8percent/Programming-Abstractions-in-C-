#include "_cctype.h"

unsigned char ccArray[256] = { 0 };

const unsigned char NUM_MASK = 0x01;
const unsigned char UP_ALPHA_MASK = 0x04;
const unsigned char DOWN_ALPHA_MASK = 0x02;

void _ccInitialize() {
	static bool isInitialize = false;

	if (!isInitialize) {
		for (char ch = '0'; ch <= '9'; ++ch)ccArray[ch] |= NUM_MASK;
		for (char ch = 'a'; ch <= 'z'; ++ch)ccArray[ch] |= DOWN_ALPHA_MASK;
		for (char ch = 'A'; ch <= 'Z'; ++ch)ccArray[ch] |= UP_ALPHA_MASK;
		
		isInitialize = true;
	}
}

bool _isdigit(char ch) {
	_ccInitialize();

	return ccArray[ch] & NUM_MASK;
}

bool _islower(char ch) {
	_ccInitialize();

	return ccArray[ch] & DOWN_ALPHA_MASK;
}

bool _isupper(char ch) {
	_ccInitialize();

	return ccArray[ch] & UP_ALPHA_MASK;
}

bool _isalpha(char ch) {
	return _isupper(ch) || _islower(ch);
}

bool _isalnum(char ch) {
	return _isalpha(ch) || _isdigit(ch);
}
