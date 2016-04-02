#pragma once
#include "sxItem.h"
#include "picaso4d.h"
#include "picaso4dConstants.h"

class sxButton : public sxItem {
public:
	sxButton(int x, int y, int width, int height, int fontsize, const char * txt)
		: sxItem(x, y, width, height, fontsize, txt) {}

	void draw(void);
};

class sxLineItem : public sxItem {
public:
	sxLineItem(int x, int y, int width, int height, int fontsize, const char * txt)
		: sxItem(x, y, width, height, fontsize, txt) {}

	void draw(void);
		
};

class sxPresetNumber : public sxItem {
public:
	sxPresetNumber(int x, int y, int width, int height, int fontsize);

	void draw(void);
	void setPresetName(const char * str);

private:

	char _presetName[32];
};

class sxBPM : public sxItem {
public:
	sxBPM(int x, int y, int width, int height)
		: sxItem(x, y, width, height, AVENIR_24, NULL) {
		setValue(1200);
	}

	void setBPM(double val);

	void draw(void);
	void drawValueChange(void);
};