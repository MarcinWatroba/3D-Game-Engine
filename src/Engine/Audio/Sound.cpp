#include <Engine\Audio\Sound.h>

Sound::Sound(string strAudioName, bool b3d, bool bloop, bool bstream, AudioEngine* engine_used)
{
	Audio = engine_used;
	Audio->Init();
	Audio->LoadSound(strAudioName, b3d, bloop, bstream);
	AudioName = strAudioName;
}

void Sound::Play(Vector3 position, float volume_In) {
	channelID = Audio->PlaySound(AudioName, position, volume_In);
}

void Sound::Stop(int channelID) {

	Audio->StopChannel(channelID);
}

int Sound::getChannelID(string strAudioName) {
	return channelID;
}