#ifndef MIDI_CLOCK_H
#define MIDI_CLOCK_H

#include <MIDI.h>

using namespace midi;

class midiClock {

  public:

    midiClock();

    void begin(MidiInterface<HardwareSerial> *midiDin, float bpm);
    void update(void);

    void setBPM(double bpm);
	double getBPM(void) { return _bpm; }

	static void(*quarterNoteCallback)(void);

  private:

     double _bpm;

	 static IntervalTimer _midiClockTimer;

};

extern midiClock MIDI_CLOCK;
#endif
