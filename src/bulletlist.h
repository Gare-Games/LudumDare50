#ifndef BULLETLIST_H
#define BULLETLIST_H

#include <vector>
#include <string>
#include "raylib.h"
#include "bullet.h"

using namespace std;

class BulletList {
	public:
		static void Initialize();
		static vector<Bullet*> bullets;
		static void RemoveBullet();
		static void AddBullet(Bullet* bullet);
		static void CleanUp();
	private:
};

#endif
