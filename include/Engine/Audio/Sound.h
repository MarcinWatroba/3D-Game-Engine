#pragma once
#include <Engine\Audio\AudioEngine.h>
#include <string>

using namespace std;

class AudioEngine;

class Sound
{
public:
	Sound() {};
	Sound(string strAudioName, bool b3d, bool bloop, bool bstream, AudioEngine* engine_used);
	~Sound() {};
	void Play(Vector3 position_In, float volume_In);
	void Stop(int channelID);

	int getChannelID(string strAudioName);
private:
	AudioEngine *Audio;
	string AudioName;
	int channelID;
};