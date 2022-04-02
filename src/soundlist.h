#ifndef SOUNDLIST_H
#define SOUNDLIST_H

#include <map>
#include <list>
#include <string>
#include "raylib.h"

using namespace std;

class SoundList {
	public:
		static void Initialize();
		static map<string, Sound> soundMap;
		static void UnloadSounds();
		static void AddSound(string name, string path);
	private:
		static list<pair<string, string>> soundNameDir;
		static void LoadSoundInternal(string name, string path);
};

#endif
