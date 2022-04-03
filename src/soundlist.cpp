#include "soundlist.h"

map<string, Sound> SoundList::soundMap;
list<pair<string, string>> SoundList::soundNameDir(
		{
			{"shoot", "resources/shoot.wav"},
			{"hitBadGuy", "resources/hitBadGuy.wav"},
			{"blockEnd", "resources/blockEnd.wav"},
			{"death", "resources/death.wav"},
			{"sizzle", "resources/sizzle.wav"},
			{"getCash", "resources/coin.wav"},
		});

void SoundList::Initialize()
{
	for(pair<string,string> p:soundNameDir)
	{
		LoadSoundInternal(p.first, p.second);
	}
}

void SoundList::UnloadSounds()
{
	//UnloadSound(sound);
	auto iter = soundMap.begin();
	while (iter != soundMap.end())
	{
		string msg = "Unloading Sound: " + iter->first;
		TraceLog(LOG_INFO, msg.c_str());

		UnloadSound(iter->second);

		msg = "Unloading Sound Complete: " + iter->first;
		TraceLog(LOG_INFO, msg.c_str());

		++iter;
	}
}

void SoundList::LoadSoundInternal(string name, string path)
{
	bool bExists = false;

	// Load into soundMap
	string msg = "Loading Sound: " + name + " From: " + path;
	TraceLog(LOG_INFO, msg.c_str());

	Sound sound = LoadSound(path.c_str());

	if (soundMap.find(name) != soundMap.end()) bExists = true;

	soundMap.insert(pair<string, Sound>(name.c_str(), sound));

	if (bExists)
	{
		msg = "Sound Overridden: " + name + " From: " + path;
		TraceLog(LOG_WARNING, msg.c_str());
	}
	else
	{
		msg = "Loading Sound Complete: " + name + " From: " + path;
		TraceLog(LOG_INFO, msg.c_str());
	}
}

void SoundList::AddSound(string name, string path)
{
	// Load into soundNameDir
	soundNameDir.push_back({name, path});

	// Load into sound Map
	LoadSoundInternal(name, path);
}

