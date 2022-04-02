#ifndef MOUSE_H
#define MOUSE_H

#include "raylib.h"

class Mouse
{
	public:
		static int lastX;
		static int lastY;
		static int x;
		static int y;
		static bool leftClickLast;
		static bool rightClickLast;
		static bool middleClickLast;
		static bool leftClick;
		static bool rightClick;
		static bool middleClick;
		static void Update();
		static bool bCursorCheck;
		static int newMouseCursor;
};

#endif
