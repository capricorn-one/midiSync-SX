#include "audioPlayer.h"
#include <Arduino.h>
#include <Audio/Audio.h>
#include "ClickSample.h"

#define VOLUME_PIN		A7

AudioPlayMemory			defaultClick;
AudioMixer4				mix1;    // two 4-channel mixers are needed in

//AudioInputI2S            i2sIn;
AudioOutputI2S	headphones;
AudioConnection	c1(defaultClick, 0, mix1, 0);

AudioConnection c8(mix1, 0, headphones, 0);
AudioConnection c9(mix1, 0, headphones, 1);

AudioControlSGTL5000     sgtl5000;

audioPlayer::audioPlayer() {
}

void audioPlayer::begin() {

	AudioMemory(12);

	//analogReadAveraging(32);
	//analogReadResolution(10);

	sgtl5000.enable();
	sgtl5000.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000.volume(0.75);

	mix1.gain(0, 0.5);

}

void audioPlayer::update() {

	//double newADC = analogRead(VOLUME_PIN);

	//Fix volume pot, if broken...no fucking sound douchebag
	//if (newADC != _volume) {
	//	sgtl5000.volume(newADC /1023.);
	//	_volume = newADC;
	//}

}

void audioPlayer::click() {
	defaultClick.play(ClickSample);
}

audioPlayer AUDIO;