#include "mouse.h"

int Mouse::lastX = 0;
int Mouse::lastY = 0;
int Mouse::x = 0;
int Mouse::y = 0;
bool Mouse::leftClickLast = false;
bool Mouse::rightClickLast = false;
bool Mouse::middleClickLast = false;
bool Mouse::leftClick = false;
bool Mouse::rightClick = false;
bool Mouse::middleClick = false;
bool Mouse::bCursorCheck = false;
int Mouse::newMouseCursor = 0;

void Mouse::Update()
{
	if(!bCursorCheck)
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	else
		SetMouseCursor(newMouseCursor);
	bCursorCheck = false;

	lastX = x;
	lastY = y;
	x = GetMouseX();
	y = GetMouseY();
	leftClickLast = leftClick;
	rightClickLast = rightClick;
	middleClickLast = middleClick;
	leftClick = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	rightClick = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
	middleClick = IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);
}
