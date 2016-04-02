#include "sxButton.h"
#include "picaso4d.h"
#include "picaso4dConstants.h"


void sxButton::draw() {
	//PICASO.gfx_Rectangle(_x, _y, _x + _width, _y + _height, BACKGROUND_COLOR);
	PICASO.gfx_Rectangle(_x, _y, _x + _width, _y + _height, THEME_COLOR);

	PICASO.txt_BGcolor(BACKGROUND_COLOR);
	PICASO.txt_FGcolor(THEME_COLOR);

	PICASO.txt_FontSD(_fontSize);
	_txtX = _x + ((_width - (PICASO.strwidth(getText()))) / 2);
	_txtY = _y + ((_height - (PICASO.strheight(getText()))) / 2);

	PICASO.gfx_MoveTo(_txtX, _txtY);
	PICASO.txt_Opacity(0);
	
	switch ( isSelected() ) {
	case NOT_SELECTED:
		PICASO.txt_Ygap(0);
		PICASO.txt_Underline(0);
		PICASO.gfx_RectangleFilled(_x + 6, _y + 6, _x + _width - 6, _y + _height - 6, BACKGROUND_COLOR);
		break;
	case SELECTED:
		PICASO.txt_Ygap(4);
		PICASO.txt_Underline(1);
		PICASO.gfx_RectangleFilled(_x + 6, _y + 6, _x + _width - 6, _y + _height - 6, BACKGROUND_COLOR);
		break;
	case EDIT_MODE:
		PICASO.gfx_RectangleFilled(_x + 6, _y + 6, _x + _width - 6, _y + _height - 6, THEME_COLOR);
		PICASO.txt_Inverse(1);
		PICASO.txt_Ygap(0);
		PICASO.txt_Underline(0);
		break;
	}
	PICASO.print(getText());
	PICASO.txt_Inverse(0);
}


void sxLineItem::draw() {
	//drawText();
	Serial.println("Draw called");
}

sxPresetNumber::sxPresetNumber(int x, int y, int width, int height, int fontsize)
	: sxItem(x, y, width, height, fontsize, "blank") {

	strcpy(_presetName, "Mike Schneider - Pole Rider");
}

void sxPresetNumber::draw() {
	PICASO.txt_Opacity(0);
	PICASO.txt_FontID(3);
	PICASO.gfx_MoveTo(80,155);
	PICASO.txt_FGcolor(THEME_COLOR);
	PICASO.print("REMOTE");
	PICASO.gfx_MoveTo(200, 155);
	PICASO.print("PROGRAM");

	PICASO.txt_FontSD(AVENIR_24);		//Need an italic font instead, custom for writing preset name
	PICASO.txt_FGcolor(THEME_COLOR_SECONDARY);
	PICASO.gfx_MoveTo(10, 175);
	PICASO.txt_Italic(1);
	PICASO.print(getValue());
	PICASO.print(" - ");
	PICASO.print(_presetName);
	PICASO.txt_Italic(0);

	PICASO.txt_FontSD(_fontSize);
	PICASO.txt_FGcolor(THEME_COLOR);
	PICASO.gfx_MoveTo(145,120);
	PICASO.print(getValue());

}

void sxPresetNumber::setPresetName(const char * str) {
	strncpy(_presetName, str, 32);
	draw();
}

void sxBPM::setBPM(double val) {
	setValue(val*10.);
}

void sxBPM::draw() {
	char buffer[8];
	double bpm = getValue() / 10.;
	snprintf(buffer, 8, "%.1f", bpm);

	PICASO.txt_FontSD(AVENIR_36);
	PICASO.txt_FGcolor(THEME_COLOR);
	PICASO.txt_Opacity(0);
	
	//PICASO.gfx_Triangle(95, 130, 225, 130, 160, 30, THEME_COLOR);

	switch (isSelected()) {
	case NOT_SELECTED:
		PICASO.gfx_TriangleFilled(104, 125, 216, 125, 160, 38, BACKGROUND_COLOR);
		PICASO.txt_Underline(0);
		break;
	case SELECTED:
		PICASO.gfx_TriangleFilled(104, 125, 216, 125, 160, 38, BACKGROUND_COLOR);
		PICASO.txt_Underline(1);
		break;
	case EDIT_MODE:
		PICASO.txt_Ygap(0);
		PICASO.txt_Inverse(1);
		PICASO.gfx_TriangleFilled(104, 125, 216, 125, 160, 38, THEME_COLOR);
		PICASO.txt_Underline(0);
	}
		
	int x = (PICASO.width() - PICASO.strwidth(buffer)) / 2;
	PICASO.gfx_MoveTo(x, 94);
	PICASO.print(buffer);

	PICASO.txt_FontSD(AVENIR_24);
	PICASO.gfx_MoveTo(142, 65);
	PICASO.print("BPM");
	PICASO.txt_Inverse(0);
}

void sxBPM::drawValueChange() {

	char buffer[8];
	double bpm = getValue() / 10.;
	if (bpm < 100.)
		snprintf(buffer, 8, " %.1f ", bpm);
	else
		snprintf(buffer, 8, "%.1f", bpm);

	PICASO.txt_FontSD(AVENIR_36);
	PICASO.txt_FGcolor(THEME_COLOR);
	PICASO.txt_Opacity(1);

	switch (isSelected()) {
	case NOT_SELECTED:
		//PICASO.gfx_RectangleFilled(120, 125, 200, 160, BLACK);
		PICASO.txt_Underline(0);
		break;
	case SELECTED:
		//PICASO.gfx_RectangleFilled(120, 125, 200, 160, BLACK);
		PICASO.txt_Underline(1);
		break;
	case EDIT_MODE:
		PICASO.txt_Ygap(0);
		//PICASO.gfx_RectangleFilled(120, 125, 200, 90, THEME_COLOR);
		PICASO.txt_Inverse(1);
		PICASO.txt_Underline(0);
	}

	int x = (PICASO.width() - PICASO.strwidth(buffer)) / 2;
	PICASO.gfx_MoveTo(x, 90);
	PICASO.print(buffer);
}