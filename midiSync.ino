#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Encoder.h>
#include <MIDI.h>
#include "midiClock.h"
#include "syncOS.h"
#include <Audio.h>
#include "audioPlayer.h"


MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiDIN);		//Switch to Serial1 for final pcb

elapsedMillis t;

syncOS os;

void setup() {

	os.begin();

	AUDIO.begin();
	
	midiDIN.begin(10);
	
	MIDI_CLOCK.begin(&midiDIN, 100.00);

	//while (1) {
	//	AUDIO.click();
	//	delay(500);
	//}
	
}

void loop() {

	
	while (usbMIDI.read()) {
		// ignore incoming messages
	}

	AUDIO.update();

	os.update();

}
