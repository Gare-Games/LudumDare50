#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <vector>
#include <string>
#include "raylib.h"
#include "item.h"

using namespace std;

class ItemList {
	public:
		static void Initialize();
		static vector<Item*> items;
		static void RemoveItem();
		static void AddItem(Item* item);
		static void CleanUp();
		static void Clear();
	private:
};

#endif
