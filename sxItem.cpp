#include "sxItem.h"
#include <EEPROM\EEPROM.h>

void(*sxItem::itemCallbackFunction)(void);

sxItem::sxItem(int x, int y, int width, int height, int fontSize, const char * txt) {
	_width = width;
	_height = height;
	_x = x;
	_y = y;
	_fontSize = fontSize;

	_txtX = _x;
	_txtY = _y;
	
	_selected = NOT_SELECTED;
	_value = 0;

	strncpy(_text, txt, MAX_STR_LENGTH);
}

void sxItem::init() {
	
}


uint8_t sxItem::touch(int x, int y) {

	if ((x - _x) < _width) {
		if ((y - _y) < _height) {
			itemCallbackFunction();
			return 1;
		}
	}
	return 0;
}

void sxItem::saveValueToEEProm(int address) {
	EEPROM.write(address, _value);
}

int sxItem::readValueFromEEProm(int address) {
	_value = EEPROM.read(address);
	return _value;
}

void sxItem::setCallback(void(*function)(void)) {
	itemCallbackFunction = function;
}