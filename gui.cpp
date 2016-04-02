#include "gui.h"
#include "sxButton.h"
#include "sxItem.h"
#include "picaso4d.h"
#include "picaso4dConstants.h"

#define MIDI_PAGE_ITEMS		2		
sxPresetNumber midiPresetNumber(100, 130, 100, 100, AVENIR_72);
sxBPM bpmItem(100, 30, 100, 100);
sxItem *midiPageItems[MIDI_PAGE_ITEMS] = { &midiPresetNumber, &bpmItem };

#define CONFIG_PAGE_ITEMS	4
sxLineItem config_midiTxChannel(5, 5, 300, 30, AVENIR_24, "MIDI Tx Channel");
sxLineItem config_midiThru(5, 35, 300, 30, AVENIR_24, "MIDI Soft Thru");
sxButton config_defaultButton(0, 145, 140, 30, AVENIR_24, "DEFAULT");
sxButton config_saveButton(179, 145, 140, 30, AVENIR_24, "SAVE");
sxItem *configPageItems[CONFIG_PAGE_ITEMS] = { &config_midiTxChannel, &config_midiThru, &config_saveButton, &config_defaultButton };

#define MENU_ITEMS			3
sxButton menuMain(0, 199, 106, 40, AVENIR_24, "MIDI");
sxButton menuAudio(106, 199, 106, 40, AVENIR_24, "AUDIO");
sxButton menuConfig(212, 199, 107, 40, AVENIR_24, "SYSTEM");
sxItem *mainMenuItems[MENU_ITEMS] = { &menuMain, &menuAudio, &menuConfig };

gui::gui() {}

void gui::begin() {

	loadSD();

	//splashVideo(4);

	PICASO.touch_Set(0);
	PICASO.touch_DetectRegion(0, 0, 320, 240);

	for (int i = 0; i < MIDI_PAGE_ITEMS; i++)
		midiPageItems[i]->init();

	for (int i = 0; i < CONFIG_PAGE_ITEMS; i++)
		configPageItems[i]->init();

	for (int i = 0; i < MENU_ITEMS; i++)
		mainMenuItems[i]->init();

	bpmItem.selectMode(EDIT_MODE);

	

}

void gui::update() {

	
}

void gui::setBPM(double val) {
	bpmItem.setBPM(val);
	bpmItem.drawValueChange();
}

void gui::setPage(uint8_t page) {

	for (int i = 0; i < MENU_ITEMS; i++) {
		if (page == i)
			mainMenuItems[i]->selectMode(EDIT_MODE);
		else
			mainMenuItems[i]->selectMode(NOT_SELECTED);
	}

	switch (page) {
	case MIDI_PAGE:
		drawMidiBackground();
		drawMidiData();
		break;
	case AUDIO_PAGE:
		drawAudioBackground();
		drawAudioData();
		break;
	case CONFIG_PAGE:
		drawConfigBackground();
		drawConfigData();
		break;
	}

	drawMenus();
}

void gui::drawMidiData() {

	midiPresetNumber.draw();
	bpmItem.draw();
}

void gui::drawMidiBackground() {

	PICASO.gfx_Triangle(95, 130, 225, 130, 160, 30, THEME_COLOR);
	PICASO.gfx_Line(95, 130, 0, 180, THEME_COLOR);
	PICASO.gfx_Line(225, 130, 319, 180, THEME_COLOR);

	PICASO.gfx_Line(147, 46, 0, 65, THEME_COLOR);
	PICASO.gfx_Line(173, 46, 319, 65, THEME_COLOR);
	//PICASO.gfx_Line(160, 60, 160, 0, THEME_COLOR);

	
	PICASO.txt_FontSD(AVENIR_36);
	PICASO.txt_FGcolor(THEME_COLOR);
	PICASO.gfx_MoveTo(240, 80);
	PICASO.print("NEXT");
	PICASO.gfx_MoveTo(15, 80);
	PICASO.print("PREV");
	
	

}

void gui::drawAudioBackground() {

}

void gui::drawAudioData() {


}

void gui::drawConfigBackground() {


}

void gui::drawConfigData() {

	config_midiTxChannel.draw();
	config_midiThru.draw();
	config_saveButton.draw();
	config_defaultButton.draw();
}

void gui::drawSaveDialog(uint8_t progress) {
	if (progress == 0) {

		PICASO.gfx_RectangleFilled(25, 60, 295, 130, BLACK);		//Clear Overlay Area
		PICASO.gfx_Rectangle(25, 60, 295, 130, THEME_COLOR);		//Draw outter box
		PICASO.gfx_Rectangle(32, 105, 288, 125, THEME_COLOR);		//Draw progress outter
		PICASO.txt_MoveCursor(3, 3);
		PICASO.txt_FontSD(AVENIR_36);
		PICASO.txt_FGcolor(THEME_COLOR);
		PICASO.print("SAVING PRESET");
	}
	else if (progress < 255) {
		if ((progress % 2) == 0)
			PICASO.gfx_Line(32 + progress, 106, 32 + progress, 126, THEME_COLOR);
	}
	else {
		PICASO.txt_MoveCursor(3, 3);
		PICASO.txt_FontSD(AVENIR_36);
		PICASO.txt_FGcolor(THEME_COLOR);
		PICASO.print("PRESET SAVED ");
	}

}

void gui::drawMenus() {

	menuMain.draw();
	menuAudio.draw();
	menuConfig.draw();
}

void gui::loadSD() {
	int disk = 0, attempts = 0;

	if ( !(disk = PICASO.fileMount()) ) {
		while (!(disk = PICASO.fileMount())) {
			PICASO.print("Drive not mounted...");
			delay(200);
			PICASO.gfx_Cls();
			if (++attempts == 10)
				return;
		}
	}
	PICASO.loadSdVideos();
	PICASO.loadSdFonts();
	
}

void gui::splashVideo(uint8_t speed) {

	for (int frame = 0; frame < 240; frame += speed)
		PICASO.video_ShowFrame(0, frame);

	PICASO.gfx_Cls();
}

gui GUI;