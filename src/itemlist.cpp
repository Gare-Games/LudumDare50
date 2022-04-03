#include "itemlist.h"

vector<Item*> ItemList::items;

void ItemList::Initialize()
{
}
void ItemList::RemoveItem()
{
}
void ItemList::AddItem(Item* item)
{
	items.push_back(item);
}

void ItemList::CleanUp()
{
	vector<Item*> newList;
	for(Item* item : items)
	{
		if(!item->bDead)
			newList.push_back(item);
	}
	items = newList;
	//items.clear();
	//items.insert(items.end(), newList.begin(), newList.end());
}

void ItemList::Clear()
{
	items.clear();
}
