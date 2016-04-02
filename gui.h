#ifndef GUI_H
#define GUI_H

#include <Arduino.h>

#define MIDI_PAGE	0
#define AUDIO_PAGE	1
#define CONFIG_PAGE	2

class gui
{
public:
	gui();

	void begin();
	void update(void);

	void setBPM(double val);

	void setPage(uint8_t p);

	
private:

	void drawMidiBackground(void);
	void drawMidiData(void);
	
	void drawAudioBackground(void);
	void drawAudioData(void);

	void drawConfigBackground(void);
	void drawConfigData(void);

	void drawSaveDialog(uint8_t progress);

	void drawMenus();

	void loadSD(void);
	void splashVideo(uint8_t speed);

};

extern gui GUI;

#endif