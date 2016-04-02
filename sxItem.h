#ifndef SX_ITEM_H
#define SX_ITEM_H

#include <Arduino.h>

#define NOT_SELECTED		0
#define SELECTED			1
#define EDIT_MODE			2

#define MAX_STR_LENGTH		16

class sxItem
{
public:

	sxItem(int x, int y, int width, int height, int fontSize, const char * txt);
	void init();
	uint8_t touch(int x, int y);		//Returns true (1) or false (0) for touch coordinates x,y
	void selectMode(uint8_t s) { _selected = s; }
	int isSelected(void) { return _selected; }
	void setCallback(void(*)(void));
	int getValue(void) { return _value; }
	void setValue(int value) { _value = value; }
	void saveValueToEEProm(int address);
	int readValueFromEEProm(int address);

	char * getText(void) { return _text; }

protected:

	int _width;
	int _height;
	int _x;
	int _y;

	int _txtX;
	int _txtY;

	int _fontSize;


private:

	int _value;
	int _selected;

	char _text[MAX_STR_LENGTH];

	static void(*itemCallbackFunction)(void);

};

#endif