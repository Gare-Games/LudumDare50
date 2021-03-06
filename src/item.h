#ifndef ITEM_H
#define ITEM_H

#include "raylib.h"
#include "texturelist.h"
#include "soundlist.h"
#include "garegames.h"
#include "globalvars.h"
#include <string>

class Item
{
	public:
		Item();
		virtual ~Item();
		Vector2 position;
		virtual void GetItem();
		void Update(float frameTime);
		void Draw();
		float duration = 8.0f; // Time till it despawns.
		bool bDead = false;
		string textureName;
		Texture2D GetTexture2D();
		Rectangle GetHitBoxLoc();

};


#endif
