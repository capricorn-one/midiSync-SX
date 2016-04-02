#include "midiClock.h"
#include "picaso4d.h"
#include "audioPlayer.h"
#include <MIDI.h>

IntervalTimer midiClock::_midiClockTimer;
MidiInterface<HardwareSerial> * _din;

volatile uint8_t clicks = 0;

static void midiClockCallback(void);

void(*midiClock::quarterNoteCallback)(void);

midiClock::midiClock() {
}

void midiClock::begin(MidiInterface<HardwareSerial> *midiDin, float bpm) {
	_din = midiDin;
	setBPM(bpm);
}

void midiClock::update() {

}

//Convert beats per minute to microseconds
//24 pulses per quarter note
//i.e. 120 bpm = 2 beats per second -> 1 beat = .5 seconds/24 = 020.833 ms = 20833 us intervals
void midiClock::setBPM(double bpm) {
  if ( (bpm > 10.0) && (bpm < 350.0) ) {
	//_midiClockTimer.end();
	_midiClockTimer.priority(0);
	_midiClockTimer.begin(midiClockCallback, 2500000. / bpm );     //midiClockTimer.begin(midiClock, (60. / bpm / 24. )*1000000 );
	_bpm = bpm;
  }
}

midiClock MIDI_CLOCK;


static void midiClockCallback() {
	
	_din->sendRealTime(Clock);
	usbMIDI.sendRealTime(Clock);
	usbMIDI.send_now();
	if (++clicks == 24) {
		//PICASO.gfx_CircleFilled(10, 10, 5, THEME_COLOR);
		clicks = 0;
		AUDIO.click();
	}
}