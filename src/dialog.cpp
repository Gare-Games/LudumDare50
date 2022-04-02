#include "dialog.h"

bool Dialog::bActiveDialogs = false;
list<Dialog*> Dialog::activeDialogs;


// Static Methods
Dialog* Dialog::GetActiveDialog()
{
	if (activeDialogs.size() > 0)
		return activeDialogs.front();
	else
		return nullptr;
}

bool Dialog::IsDialogActive()
{
	return activeDialogs.size() > 0;
}

void Dialog::RemoveDialog(Dialog* dialog)
{
	//list<Dialog*>::iterator findIter = find(activeDialogs.begin(), activeDialogs.end(), dialog);
	activeDialogs.remove(dialog);
}

Dialog* Dialog::CreateNewDialog(string dialogTitle, string trueButtonText, string falseButtonText, string dialogMessage)
{
	// Spawn in middle of screen.
	
	// Title of window.
	// Figure out the width of the popup based on the message?
	Dialog* dialog = new HireMuscle();

	dialog->title = dialogTitle;
	dialog->yesButtonText = trueButtonText;
	dialog->noButtonText = falseButtonText;
	dialog->message = dialogMessage;

	dialog->width = 300;
	dialog->height = 200;

	dialog->x = (GetScreenWidth()/2) - (dialog->width/2); 
	dialog->y = (GetScreenHeight()/2) - (dialog->height/2); 

	activeDialogs.push_back(dialog);
	bActiveDialogs = true;
	return dialog;
}

// Static Methods - END

// Object Methods
void Dialog::Update()
{
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	bYesButtonCollision = Collision::PointWithRect(GetMousePosition(), {x+30, y+height-yesButtonHeight-buttonPaddingBottom, yesButtonWidth, yesButtonHeight});

	bNoButtonCollision = Collision::PointWithRect(GetMousePosition(), {x+width-noButtonWidth-30, y+height-noButtonHeight-buttonPaddingBottom, noButtonWidth, noButtonHeight});

	bool bTopBarCollisionLast = bTopBarCollision;

	if (!bYesInitialClick && !bNoInitialClick && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (bYesButtonCollision)
		{
			bYesInitialClick = true;
		}
		else if(bNoButtonCollision)
		{
			bNoInitialClick = true;
		}
	}

	bTopBarCollision = Collision::PointWithRect(GetMousePosition(), {x, y, width, topBarHeight});

	if (bTopBarCollision || bYesButtonCollision || bNoButtonCollision)
	{
		Mouse::bCursorCheck = true;
		Mouse::newMouseCursor = MOUSE_CURSOR_POINTING_HAND;

		if (bYesButtonCollision && !IsYesAvailable())
			Mouse::newMouseCursor = MOUSE_CURSOR_NOT_ALLOWED;
		else if (bNoButtonCollision && !IsNoAvailable())
			Mouse::newMouseCursor = MOUSE_CURSOR_NOT_ALLOWED;
	}

	if (bTopBarCollisionLast)
	{
		if (Mouse::leftClickLast && Mouse::leftClick)
		{
			int xDiff = Mouse::x - Mouse::lastX;
			int yDiff = Mouse::y - Mouse::lastY;

			x = min(max(0, x + xDiff), GetScreenWidth() - width);
			y = min(max(0, y + yDiff), GetScreenHeight() - height);

			// This means collision should still be valid. Override earlier check.
			bTopBarCollision = true;
		}
	} 
	if (bYesInitialClick && bYesButtonCollision && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		YesSelected();
		ClearInitialClicks();
	} else if (bNoInitialClick && bNoButtonCollision && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		NoSelected();
		ClearInitialClicks();
	} else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		// Clear all initial clicks
		ClearInitialClicks();
	}
}

void Dialog::ClearInitialClicks()
{
	bYesInitialClick = false;
	bNoInitialClick = false;
}

void Dialog::YesSelected()
{
	TraceLog(LOG_INFO, TextFormat("YesSelected()"));
	RemoveDialog(this);
}

void Dialog::NoSelected()
{
	TraceLog(LOG_INFO, TextFormat("NoSelected()"));
	RemoveDialog(this);
}

// Probably shouldn't do any calculations here.
void Dialog::DrawDialog()
{
	Color colorOutlineYes = WHITE;
	if (bYesButtonCollision) colorOutlineYes = GREEN;
	Color colorOutlineNo = WHITE;
	if (bNoButtonCollision) colorOutlineNo = GREEN;
	Color colorOutlineTopBar = WHITE;
	if (bTopBarCollision) colorOutlineTopBar = GREEN;
	// I could probably use some nice textures or something...
	
	// Background
	DrawRectangle(x, y, width, height, BLACK);

	// Window Outline
	DrawRectangleLines(x+1, y+1, width-2, height-2, WHITE);
	DrawRectangleLines(x, y, width, height, WHITE);

	// Top Bar
	DrawRectangleLines(x+1, y+1, width-2, topBarHeight-2, colorOutlineTopBar);
	DrawRectangleLines(x, y, width, topBarHeight, colorOutlineTopBar);
	DrawText(title.c_str(), x+5, y+5, 5, WHITE);

	DrawText(message.c_str(), x+5, y + topBarHeight + 5, 5, WHITE);

	// Yes Button
	DrawRectangleLines(x+30+1, y+height-yesButtonHeight+1-buttonPaddingBottom, yesButtonWidth-2, yesButtonHeight-2, colorOutlineYes);
	DrawRectangleLines(x+30, y+height-yesButtonHeight-buttonPaddingBottom, yesButtonWidth, yesButtonHeight, colorOutlineYes);

	int yesTextOffsetX = yesButtonText.size();
	DrawText(yesButtonText.c_str(), x+30 + (yesButtonWidth/2) - yesTextOffsetX, y+height-yesButtonHeight-buttonPaddingBottom+5+(yesButtonHeight/4), 5, IsYesAvailable() ? WHITE : GRAY);
	
	// No Button
	DrawRectangleLines(x+width-noButtonWidth-30+1, y+height-noButtonHeight+1-buttonPaddingBottom, noButtonWidth-2, noButtonHeight-2, colorOutlineNo);
	DrawRectangleLines(x+width-noButtonWidth-30, y+height-noButtonHeight-buttonPaddingBottom, noButtonWidth, noButtonHeight, colorOutlineNo);

	int noTextOffsetX = noButtonText.size();
	DrawText(noButtonText.c_str(), x+width-noButtonWidth-30 + (noButtonWidth/2) - noTextOffsetX, y+height-noButtonHeight-buttonPaddingBottom+5+(noButtonHeight/4), 5, IsNoAvailable() ? WHITE : GRAY);
}
bool Dialog::IsYesAvailable() {return true;}
bool Dialog::IsNoAvailable() {return true;}
// Object Methods - END
//

// HireMuscle Implementation
void HireMuscle::YesSelected()
{
	TraceLog(LOG_INFO, TextFormat("HireMuscle::YesSelected()"));
	if (IsYesAvailable())
		RemoveDialog(this);
}

void HireMuscle::NoSelected()
{
	TraceLog(LOG_INFO, TextFormat("HireMuscle::NoSelected()"));
	if (IsNoAvailable())
		RemoveDialog(this);
}
bool HireMuscle::IsYesAvailable() {return false;}
bool HireMuscle::IsNoAvailable() {return true;}
// HireMuscle Implementation - End
