#include <Arduino.h>
#include "syncOS.h"
#include "picaso4d.h"
#include "gui.h"


Encoder encoder(29, 30);

syncOS::syncOS() {
}

void syncOS::begin() {

	PICASO.begin();

	GUI.begin();

	GUI.setPage(MIDI_PAGE);

	GUI.setBPM(MIDI_CLOCK.getBPM());

	
}

void syncOS::update() {

	//static elapsedMillis holdTime;
	//static int state;

	//state = PICASO.touch_Get(0x0000);
	//switch (state) {
	//case 1:		//Press
	//case 3:		//Moving
	//	Serial.println("Pressed");
	//case 2:		//Release
	//	Serial.println("Released");
	//	//drawSaveDialog(0);
	//	break;
	//case 0:		//Invalid/No touch
	//default:
	//	break;
	//}

	readEncoder();

}

void syncOS::readEncoder() {

	long newPosition = encoder.read();

	if (newPosition != _encoderPosition)
		MIDI_CLOCK.setBPM(MIDI_CLOCK.getBPM() + (newPosition - _encoderPosition)*0.1);
	
	GUI.setBPM(MIDI_CLOCK.getBPM());
	_encoderPosition = newPosition;

}