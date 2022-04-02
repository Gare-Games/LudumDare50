#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "texturelist.h"
#include "player.h"
#include "dialog.h"
#include "mouse.h"
#include "garegames.h"
#include "collision.h"
#include "colors.h"

#define GL_SRC_ALPHA 0x0302
#define GL_MIN 0x8007

// Initialization
//--------------------------------------------------------------------------------------
int screenWidth = 1920;
int screenHeight = 1080;

Camera2D screenSpaceCamera; // Smoothing camera

Texture2D* houseTexture;
Texture2D* hqTexture;
Texture2D* playerTexture;

RenderTexture2D fogOfWarTexture;


Player* player;

bool bLeftMouseLast = false;
int mouseXLast = -1;
int mouseYLast = -1;

int moveToX = 0;
int moveToY = 0;

int GetMouseWorldX();
int GetMouseWorldY();


int GetMouseWorldX()
{
	return GetScreenToWorld2D(GetMousePosition(), screenSpaceCamera).x;
}
int GetMouseWorldY()
{
	return GetScreenToWorld2D(GetMousePosition(), screenSpaceCamera).y;
}

void Initialize()
{
    // Initialization
    //--------------------------------------------------------------------------------------

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Smash the Swarm!");

	// Load Textures
	TextureList::Initialize();

	//ToggleFullscreen();
    screenSpaceCamera = { 0 }; // Smoothing camera
    screenSpaceCamera.zoom = 1.00f;
	screenSpaceCamera.offset = (Vector2) { screenWidth/2.0f, screenHeight/2.0f };
	screenSpaceCamera.target.x = screenWidth/2;
	screenSpaceCamera.target.y = screenHeight/2;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
	player = new Player();
	player->position.x = 350;
	player->position.y = 640;
}

int main(void)
{

	Initialize();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
		if (IsWindowResized() && !IsWindowFullscreen())
		{
			screenWidth = GetScreenWidth();
			screenHeight = GetScreenHeight();
			screenSpaceCamera.offset = (Vector2) { screenWidth/2.0f, screenHeight/2.0f };
		}

		Mouse::Update();


		// Mouse Wheel Camera Zoom
		if (GetMouseWheelMove() != 0)
		{
			screenSpaceCamera.zoom += ((float)GetMouseWheelMove()*0.05f);
        	if (screenSpaceCamera.zoom > 3.0f) screenSpaceCamera.zoom = 3.0f;
        	else if (screenSpaceCamera.zoom < 0.25f) screenSpaceCamera.zoom = 0.25f;

			TraceLog(LOG_INFO, TextFormat("Zoom: %i", screenSpaceCamera.zoom));
		}

		screenSpaceCamera.target.x = player->position.x;
		screenSpaceCamera.target.y = player->position.y;

		//Update your windows.
		if (Dialog::IsDialogActive())
		{
			Dialog::GetActiveDialog()->Update();
		}


		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			moveToX = GetMouseWorldX();
			moveToY = GetMouseWorldY();
		}

		// Better have an in order list of what occurs.
		// Keyboard Controls
		if (IsKeyDown(KEY_W)) player->position.y--;
		if (IsKeyDown(KEY_A)) player->position.x--;
		if (IsKeyDown(KEY_S)) player->position.y++;
		if (IsKeyDown(KEY_D)) player->position.x++;

		// Shoot Direction
		if (IsKeyDown(KEY_UP)) player->position.y--;
		if (IsKeyDown(KEY_LEFT)) player->position.x--;
		if (IsKeyDown(KEY_DOWN)) player->position.y++;
		if (IsKeyDown(KEY_RIGHT)) player->position.x++;

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(DB32_WHITE);

			// Draw what you can see.

            BeginMode2D(screenSpaceCamera);
				player->DrawPlayer();
            EndMode2D();


			// Gui on top of screen
			// Maybe draw to texture?
			DrawRectangle(0,0, screenWidth, 60, DB32_BLACK);
			GareGames::DrawTextureRect(TextureList::textureMap["bottomUIFill1"], 0, screenHeight - 200, screenWidth, 200, DB32_WHITE);
			GareGames::DrawTextureRect(TextureList::textureMap["bottomUILSide"], 0, screenHeight - 200, 15, 200, DB32_WHITE);
			GareGames::DrawTextureRect(TextureList::textureMap["bottomUIRSide"], screenWidth - 15, screenHeight - 200, 15, 200, DB32_WHITE);


			//Draw you windows here.
			if (Dialog::IsDialogActive())
			{
				Dialog::GetActiveDialog()->DrawDialog();
			}
			
            DrawText(TextFormat("Screen resolution: %ix%i", screenWidth, screenHeight), 10, 10, 20, DB32_DARKBLUEPURPLE);
            DrawFPS(GetScreenWidth() - 95, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
	TextureList::UnloadTextures();	// Unloads all the textures in TextureList

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
