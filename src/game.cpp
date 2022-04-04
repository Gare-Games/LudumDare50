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
#include "soundlist.h"
#include "enemy.h"
#include "enemylist.h"
#include "itemlist.h"
#include "spawner.h"
#include "level.h"
#include "globalVars.h"

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

Level* level1;

RenderTexture2D fogOfWarTexture;


Player* player;

bool bGameOver = false;
bool bPaused = false;
bool bLeftMouseLast = false;
bool bDebug = false;
int mouseXLast = -1;
int mouseYLast = -1;
float infoTimer = 6.0f;

int moveToX = 0;
int moveToY = 0;

int GetMouseWorldX();
int GetMouseWorldY();
void ResetGame();
void GameOver();

float thisFrameTime = 0.0f;
float lastFrameTime = 0.0f;
float timeSurvived = 0.0f;


int GetMouseWorldX()
{
	return GetScreenToWorld2D(GetMousePosition(), screenSpaceCamera).x;
}
int GetMouseWorldY()
{
	return GetScreenToWorld2D(GetMousePosition(), screenSpaceCamera).y;
}

Vector2 GetMouseWorldPos()
{
	return GetScreenToWorld2D(GetMousePosition(), screenSpaceCamera);
}

void Initialize()
{
    // Initialization
    //--------------------------------------------------------------------------------------

	// Set this later if you want resizable windows. Will probably break the game.
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Smash the Swarm!");
	InitAudioDevice();

	// Load Textures
	TextureList::Initialize();
	SoundList::Initialize();

	//ToggleFullscreen();
    screenSpaceCamera = { 0 }; // Smoothing camera
    screenSpaceCamera.zoom = 1.00f;
	screenSpaceCamera.offset = (Vector2) { screenWidth/2.0f, screenHeight/2.0f };
	screenSpaceCamera.target.x = screenWidth/2;
	screenSpaceCamera.target.y = screenHeight/2;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
	player = new Player();
	player->position = (Vector2) { screenWidth/2.0f, screenHeight/2.0f };
	player->currentWeapon = new Pistol(player);
	player->defaultWeapon = player->currentWeapon;
	player->shootDirection = Direction::DOWN;
	player->moveDirection = Direction::DOWN;
	GlobalVars::player = player;

	level1 = new Level();

	level1->AddSpawnJob(EnemyType::Main, SpawnLocation::LEFT, -1, 2.0f, 1.5f);
	level1->AddSpawnJob(EnemyType::Main, SpawnLocation::RIGHT, -1, 2.0f, 1.5f);

	level1->AddSpawnJob(EnemyType::ITEM_Cash, SpawnLocation::RIGHT, -1, 9.0f, 10.0f);

	// Introduce first new baddie here.
	level1->AddSpawnJob(EnemyType::Tough, SpawnLocation::RIGHT, -1, 20.0f, 6.0f);
	level1->AddSpawnJob(EnemyType::Tough, SpawnLocation::LEFT, -1, 22.0f, 6.0f);

	level1->AddSpawnJob(EnemyType::ITEM_Rifle, SpawnLocation::RIGHT, -1, 27.0f, 6.0f);

	level1->AddSpawnJob(EnemyType::Tough, SpawnLocation::DOWN, -1, 40.0f, 6.0f);

	// Probably should spawn an item here.


	level1->AddSpawnJob(EnemyType::Main, SpawnLocation::UP, -1, 45.0f, 3.0f);
	level1->AddSpawnJob(EnemyType::Main, SpawnLocation::DOWN, -1, 65.0f, 4.5f);

	level1->AddSpawnJob(EnemyType::Tough, SpawnLocation::UP, -1, 90.0f, 6.0f);


	// Introduce second baddie here.
	level1->AddSpawnJob(EnemyType::Fast, SpawnLocation::UP, -1, 95.0f, 10.0f);
	level1->AddSpawnJob(EnemyType::Fast, SpawnLocation::DOWN, -1, 125.0f, 10.0f);
	level1->AddSpawnJob(EnemyType::Fast, SpawnLocation::LEFT, -1, 165.0f, 10.0f);
	level1->AddSpawnJob(EnemyType::Fast, SpawnLocation::RIGHT, -1, 245.0f, 10.0f);
	level1->AddSpawnJob(EnemyType::Fast, SpawnLocation::UP, -1, 365.0f, 10.0f);
	level1->AddSpawnJob(EnemyType::Fast, SpawnLocation::DOWN, -1, 425.0f, 10.0f);
	level1->AddSpawnJob(EnemyType::Fast, SpawnLocation::LEFT, -1, 485.0f, 10.0f);
	level1->AddSpawnJob(EnemyType::Fast, SpawnLocation::RIGHT, -1, 565.0f, 10.0f);
	level1->AddSpawnJob(EnemyType::Fast, SpawnLocation::UP, -1, 525.0f, 10.0f);
	level1->AddSpawnJob(EnemyType::Fast, SpawnLocation::DOWN, -1, 525.0f, 10.0f);


	//Finish. Little time left now.

}

int main(void)
{

	Initialize();

	level1->Start();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		lastFrameTime = thisFrameTime;
		thisFrameTime = GetFrameTime();
		infoTimer = max(0.0f, infoTimer-thisFrameTime);

        // Update
        //----------------------------------------------------------------------------------
		//if (IsWindowResized() && !IsWindowFullscreen())
		//{
		//	screenWidth = GetScreenWidth();
		//	screenHeight = GetScreenHeight();
		//	screenSpaceCamera.offset = (Vector2) { screenWidth/2.0f, screenHeight/2.0f };
		//}

		level1->Update(thisFrameTime);

		Mouse::Update();
		player->currentWeapon->Update(thisFrameTime);
		for (Bullet* bullet : BulletList::bullets)
		{
			bullet->Update(thisFrameTime);
		}
		
		for (Enemy* enemy : EnemyList::enemys)
		{
			enemy->Update(thisFrameTime);
		}

		for (Item* item : ItemList::items)
		{
			item->Update(thisFrameTime);
		}


		// Check collisions here.
		for (Enemy* enemy : EnemyList::enemys)
		{
			if(enemy->bDead) continue;

			for (Bullet* bullet : BulletList::bullets)
			{
				if(bullet->bDead) continue;
				if (Collision::RectWithRect(enemy->GetHitBoxLoc(), bullet->GetHitBoxLoc()))
				{
					bullet->bDead = true;
					enemy->TakeDamage(bullet->damage);
					PlaySound(SoundList::soundMap["hitBadGuy"]);
					if (enemy->bDead)
						GlobalVars::score += 5;
					break;
				}
			}
		}

		if (!bGameOver)
		{
			timeSurvived += thisFrameTime;
		}

		EnemyList::CleanUp();
		BulletList::CleanUp();
		ItemList::CleanUp();

		//Check for collision with player == death!
		for (Enemy* enemy : EnemyList::enemys)
		{
			if (Collision::RectWithRect(enemy->GetAttackBoxLoc(), player->GetHitBoxLoc()))
			{
				//Trigger game reset
				if (!bGameOver)
				{
					GameOver();
				}
			}
		}

		//Check for collision with player. Trigger collection
		for (Item* item : ItemList::items)
		{
			if (Collision::RectWithRect(item->GetHitBoxLoc(), player->GetHitBoxLoc()))
			{
				item->GetItem();	
			}
		}

		// Mouse Wheel Camera Zoom
//		if (GetMouseWheelMove() != 0)
//		{
//			screenSpaceCamera.zoom += ((float)GetMouseWheelMove()*0.05f);
//        	if (screenSpaceCamera.zoom > 3.0f) screenSpaceCamera.zoom = 3.0f;
//        	else if (screenSpaceCamera.zoom < 0.25f) screenSpaceCamera.zoom = 0.25f;
//
//		}
//
		//screenSpaceCamera.target.x = player->position.x;
		//screenSpaceCamera.target.y = player->position.y;

		//Update your windows.
		if (Dialog::IsDialogActive())
		{
			Dialog::GetActiveDialog()->Update();
		}

		// Better have an in order list of what occurs.
		// Keyboard Controls
		if (IsKeyPressed(KEY_F)) bDebug = !bDebug;

		if (!bGameOver)
		{
			// Move Direction
			if (IsKeyDown(KEY_S) || IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
			{
				if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D)) player->moveDirection = Direction::DOWNRIGHT;
				else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) player->moveDirection = Direction::DOWNLEFT;
				else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) player->moveDirection = Direction::UPRIGHT;
				else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) player->moveDirection = Direction::UPLEFT;
				else if (IsKeyDown(KEY_W)) player->moveDirection = Direction::UP;
				else if (IsKeyDown(KEY_A)) player->moveDirection = Direction::LEFT;
				else if (IsKeyDown(KEY_S)) player->moveDirection = Direction::DOWN;
				else if (IsKeyDown(KEY_D)) player->moveDirection = Direction::RIGHT;
				player->Move();
			}

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
		}
		else
		{
			if (IsKeyPressed(KEY_R)) 
			{
				// Reset Function;
				ResetGame();
			}
		}

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(DB32_WHITE);

			// Draw what you can see.

            BeginMode2D(screenSpaceCamera);
				DrawTexture(TextureList::textureMap["level1bg"], 0, 0, WHITE);
				if(infoTimer > 0)
				{
					DrawTexture(TextureList::textureMap["keypad"], 400, 50, WHITE);
				}
				// Draw Item List
				for (Item* item : ItemList::items)
				{
					item->Draw();
				}

				player->DrawPlayer();
				if (bDebug)
				{
					DrawRectangleLinesEx(player->GetHitBoxLoc(), 1, DB32_GREEN);	
				}


				//Draw a debug dot to represent shoot direction.
					Vector2 weaponExitPosition = player->currentWeapon->WeaponExitPosition(player->position, player->shootDirection);
					DrawRectangle(weaponExitPosition.x, weaponExitPosition.y, 3, 3, DB32_GREEN);
				if (bDebug)
				{
				}

				for (Bullet* bullet : BulletList::bullets)
				{
					bullet->Draw();
				}

				for (Enemy* enemy : EnemyList::enemys)
				{
					enemy->Draw();
					if (bDebug)
					{
						DrawRectangleLinesEx(enemy->GetHitBoxLoc(), 1, DB32_RED);	
						DrawRectangleLinesEx(enemy->GetAttackBoxLoc(), 1, DB32_GREEN);	
					}
				}


				DrawTexture(TextureList::textureMap["topdoor"], 280, 0, WHITE);
				DrawTexture(TextureList::textureMap["leftdoor"], 0, 195, WHITE);
				DrawTexture(TextureList::textureMap["rightdoor"], 759, 195, WHITE);
				DrawTexture(TextureList::textureMap["bottomdoor"], 280, 558, WHITE);
            EndMode2D();


			// Gui on top of screen
			// Maybe draw to texture?
			//GareGames::DrawTextureRect(TextureList::textureMap["bottomUIFill1"], 0, -15, screenWidth, 100, DB32_WHITE);
			//GareGames::DrawTextureRect(TextureList::textureMap["bottomUILSide"], 0, -15, 15, 100, DB32_WHITE);
			//GareGames::DrawTextureRect(TextureList::textureMap["bottomUIRSide"], screenWidth - 15, -15, 15, 100, DB32_WHITE);


			//Draw you windows here.
			if (Dialog::IsDialogActive())
			{
				Dialog::GetActiveDialog()->DrawDialog();
			}
			
            DrawText(TextFormat("AMMO: %i", player->currentWeapon->rounds), 40, 5, 20, DB32_GREEN);
			DrawText(TextFormat("SCORE: %i", GlobalVars::score), GetScreenWidth()-200, 5, 20, DB32_GREEN);
			DrawText(TextFormat("ALIVE TIME: %.2f", timeSurvived), GetScreenWidth()-470, 5, 20, DB32_GREEN);

			if (bGameOver) DrawText(TextFormat("GAME OVER"), 320, 260, 35, DB32_RED);
			if (bGameOver) DrawText(TextFormat("Press R to restart "), 320, 300, 15, DB32_GREEN);
			if (bGameOver) DrawText(TextFormat("Press R to restart "), 320, 300, 15, DB32_GREEN);
            //DrawFPS(GetScreenWidth() - 95, 10);
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

void GameOver()
{
	bGameOver = true;
	PlaySound(SoundList::soundMap["death"]);
	level1->Stop();
}

void ResetGame()
{
	EnemyList::Clear();
	BulletList::Clear();
	ItemList::Clear();
	bGameOver = false;
	level1->Reset();
	player->position = (Vector2) { screenWidth/2.0f, screenHeight/2.0f };
	player->currentWeapon = new Pistol(player);
	player->shootDirection = Direction::DOWN;
	player->moveDirection = Direction::DOWN;
	GlobalVars::score = 0;
	level1->Start();
	timeSurvived = 0;
}
