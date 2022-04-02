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
#include "weapon.h"
#include "pistol.h"
#include "bullet.h"
#include "bulletlist.h"

#define GL_SRC_ALPHA 0x0302
#define GL_MIN 0x8007

// Initialization
//--------------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 600;

Camera2D screenSpaceCamera; // Smoothing camera

Texture2D* houseTexture;
Texture2D* hqTexture;
Texture2D* playerTexture;

RenderTexture2D fogOfWarTexture;


Player* player;

bool bLeftMouseLast = false;
bool bDebug = true;
int mouseXLast = -1;
int mouseYLast = -1;

int moveToX = 0;
int moveToY = 0;

int GetMouseWorldX();
int GetMouseWorldY();

float thisFrameTime = 0.0f;
float lastFrameTime = 0.0f;


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

	// Set this later if you want resizable windows. Will probably break the game.
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
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
	player->currentWeapon = new Pistol(player);
	player->shootDirection = Direction::DOWN;
	player->moveDirection = Direction::DOWN;
}

int main(void)
{

	Initialize();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		lastFrameTime = thisFrameTime;
		thisFrameTime = GetFrameTime();
		//TraceLog(LOG_INFO, TextFormat("Last: %f This: %f", lastFrameTime, thisFrameTime));

        // Update
        //----------------------------------------------------------------------------------
		//if (IsWindowResized() && !IsWindowFullscreen())
		//{
		//	screenWidth = GetScreenWidth();
		//	screenHeight = GetScreenHeight();
		//	screenSpaceCamera.offset = (Vector2) { screenWidth/2.0f, screenHeight/2.0f };
		//}

		Mouse::Update();
		player->currentWeapon->Update(thisFrameTime);
		for (Bullet* bullet : BulletList::bullets)
		{
			bullet->Update(thisFrameTime);
		}
		


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
		if (IsKeyPressed(KEY_F)) bDebug = !bDebug;

		// Shoot Direction
		if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT))
		{
			if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_RIGHT)) player->shootDirection = Direction::DOWNRIGHT;
			else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT)) player->shootDirection = Direction::DOWNLEFT;
			else if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_RIGHT)) player->shootDirection = Direction::UPRIGHT;
			else if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_LEFT)) player->shootDirection = Direction::UPLEFT;
			else if (IsKeyDown(KEY_UP)) player->shootDirection = Direction::UP;
			else if (IsKeyDown(KEY_LEFT)) player->shootDirection = Direction::LEFT;
			else if (IsKeyDown(KEY_DOWN)) player->shootDirection = Direction::DOWN;
			else if (IsKeyDown(KEY_RIGHT)) player->shootDirection = Direction::RIGHT;
			player->currentWeapon->Trigger();
		}

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(DB32_WHITE);

			// Draw what you can see.

            BeginMode2D(screenSpaceCamera);
				DrawRectangle(350,640, 50, 60, DB32_RED);
				DrawRectangle(550,540, 50, 60, DB32_RED);
				DrawRectangle(450,440, 50, 60, DB32_RED);
				DrawRectangle(350,540, 50, 60, DB32_RED);
				player->DrawPlayer();


				//Draw a debug dot to represent shoot direction.
				if (bDebug)
				{
					switch(player->shootDirection)
					{
						case Direction::UP:
							DrawRectangle(player->position.x, player->position.y - 30, 3, 3, DB32_GREEN);
							break;
						case Direction::DOWN:
							DrawRectangle(player->position.x, player->position.y + 30, 3, 3, DB32_GREEN);
							break;
						case Direction::DOWNLEFT:
							DrawRectangle(player->position.x-30, player->position.y + 30, 4, 5, DB32_GREEN);
							break;
						case Direction::DOWNRIGHT:
							DrawRectangle(player->position.x+30, player->position.y + 30, 3, 5, DB32_GREEN);
							break;
						case Direction::UPLEFT:
							DrawRectangle(player->position.x-30, player->position.y - 30, 3, 3, DB32_GREEN);
							break;
						case Direction::UPRIGHT:
							DrawRectangle(player->position.x+30, player->position.y - 30, 3, 3, DB32_GREEN);
							break;
						case Direction::LEFT:
							DrawRectangle(player->position.x-30, player->position.y, 3, 3, DB32_GREEN);
							break;
						case Direction::RIGHT:
							DrawRectangle(player->position.x+30, player->position.y, 3, 3, DB32_GREEN);
							break;
					}
				}

				for (Bullet* bullet : BulletList::bullets)
				{
					bullet->Draw();
				}
            EndMode2D();


			// Gui on top of screen
			// Maybe draw to texture?
			DrawRectangle(0,0, screenWidth, 60, DB32_BLACK);
			GareGames::DrawTextureRect(TextureList::textureMap["bottomUIFill1"], 0, 0, screenWidth, 100, DB32_WHITE);
			GareGames::DrawTextureRect(TextureList::textureMap["bottomUILSide"], 0, 0, 15, 100, DB32_WHITE);
			GareGames::DrawTextureRect(TextureList::textureMap["bottomUIRSide"], screenWidth - 15, 0, 15, 100, DB32_WHITE);


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
