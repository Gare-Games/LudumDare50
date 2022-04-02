#ifndef TEXTURELIST_H
#define TEXTURELIST_H

#include <map>
#include <list>
#include <string>
#include "raylib.h"

using namespace std;

class TextureList {
	public:
		static void Initialize();
		static map<string, Texture2D> textureMap;
		static void UnloadTextures();
		static void AddTexture(string name, string path);
	private:
		static list<pair<string, string>> textureNameDir;
		static void LoadTextureInternal(string name, string path);
};

#endif
