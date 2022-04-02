#ifndef DIALOG_H
#define DIALOG_H

#include "raylib.h"
#include "collision.h"
#include "mouse.h"
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class Dialog
{
	public:
		// Static
		static bool IsDialogActive();
		static Dialog* GetActiveDialog();
		static Dialog* CreateNewDialog(string dialogTitle, string trueButtonText, string falseButtonText, string dialogMessage);
		static void RemoveDialog(Dialog*);

		// Object
		void Update();
		void DrawDialog();
		void ClearInitialClicks();
		virtual void YesSelected();
		virtual void NoSelected();
		virtual bool IsYesAvailable();
		virtual bool IsNoAvailable();

	private:
		// Static
		static bool bActiveDialogs;
		static list<Dialog*> activeDialogs;
		
		// Object
		int x;
		int y;
		int width;
		int height;
		string title;
		string yesButtonText;
		string noButtonText;
		string message;
		int topBarHeight = 30;
		int yesButtonWidth = 80;
		int noButtonWidth = 80;
		int yesButtonHeight = 30;
		int noButtonHeight = 30;
		int buttonPaddingBottom = 5;
		
		bool bYesButtonCollision = false;
		bool bNoButtonCollision = false;
		bool bTopBarCollision = false;

		bool bYesInitialClick = false;
		bool bNoInitialClick = false;
};

class HireMuscle : public Dialog
{
	public:
		void YesSelected();
		void NoSelected();
		bool IsYesAvailable();
		bool IsNoAvailable();
};

#endif
