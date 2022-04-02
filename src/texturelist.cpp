#include "texturelist.h"

map<string, Texture2D> TextureList::textureMap;
list<pair<string, string>> TextureList::textureNameDir(
		{
			{"house", "resources/house.png"},
			{"hq", "resources/hq.png"},
			{"person", "resources/character.png"},
			{"foggy", "resources/foggy.png"},
			{"bottomUIFill50", "resources/bottomUIFiller50.png"},
			{"bottomUIFill1", "resources/bottomUIFiller1.png"},
			{"bottomUILSide", "resources/bottomUILSide.png"},
			{"bottomUIRSide", "resources/bottomUIRSide.png"},
			{"player", "resources/player.png"},
		});

void TextureList::Initialize()
{
	for(pair<string,string> p:textureNameDir)
	{
		LoadTextureInternal(p.first, p.second);
	}
}

void TextureList::UnloadTextures()
{
	//UnloadTexture(texture);
	auto iter = textureMap.begin();
	while (iter != textureMap.end())
	{
		string msg = "Unloading Texture: " + iter->first;
		TraceLog(LOG_INFO, msg.c_str());

		UnloadTexture(iter->second);

		msg = "Unloading Texture Complete: " + iter->first;
		TraceLog(LOG_INFO, msg.c_str());

		++iter;
	}
}

void TextureList::LoadTextureInternal(string name, string path)
{
	bool bExists = false;

	// Load into textureMap
	string msg = "Loading Texture: " + name + " From: " + path;
	TraceLog(LOG_INFO, msg.c_str());

	Texture2D texture = LoadTexture(path.c_str());

	if (textureMap.find(name) != textureMap.end()) bExists = true;

	textureMap.insert(pair<string, Texture2D>(name.c_str(), texture));

	if (bExists)
	{
		msg = "Texture Overridden: " + name + " From: " + path;
		TraceLog(LOG_WARNING, msg.c_str());
	}
	else
	{
		msg = "Loading Texture Complete: " + name + " From: " + path;
		TraceLog(LOG_INFO, msg.c_str());
	}
}

void TextureList::AddTexture(string name, string path)
{
	// Load into textureNameDir
	textureNameDir.push_back({name, path});

	// Load into texture Map
	LoadTextureInternal(name, path);
}

