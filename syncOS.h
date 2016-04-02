#ifndef _SYNC_OS_H
#define _SYNC_OS_H

#include "midiClock.h"
#include "gui.h"
#include <Encoder.h>

#define OS_STOPPED		0
#define OS_PLAYING		1
#define OS_PAUSED		2

class syncOS
{
public:
	syncOS(void);

	void begin(void);
	void update(void);

private:

	int _preset;
	double _BPM;
	char * _name;

	int _displayPreset;
	double _displayBPM;
	char * _displayName;

	long _encoderPosition;

	void readEncoder();
};

#endif