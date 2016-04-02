#ifndef AUDIO_PLAYER
#define AUDIO_PLAYER

#include <Arduino.h>

class audioPlayer
{
public:
	audioPlayer();

	void begin(void);
	void update(void);
	
	void click(void);


private:

	int _volume;
};

extern audioPlayer AUDIO;
#endif