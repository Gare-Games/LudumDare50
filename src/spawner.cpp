#include "spawner.h"


SpawnJob::SpawnJob(EnemyType enemyType, SpawnLocation location, int amount, float startTime, float interval)
{
	this->enemyType = enemyType;	
	this->location = location;	
	this->amount = amount;	
	this->startTime = startTime;	
	this->interval = interval;	
	this->startTimer = startTime;	
	this->intervalTimer = interval;	
}
void SpawnJob::Reset()
{
	spawned = 0;	
	bStart = false;
	bDone = false;
	intervalTimer = interval;
	startTimer = startTime;
}
void SpawnJob::Update(float frameTime)
{
	if(bDone) return;

	if(!bStart)
	{
		startTimer = max(0.0f, startTimer-frameTime);
		if (startTimer == 0.0f)
		{
			bStart = true;
		}
		else
		{
		}
	}
	else
	{
		intervalTimer = max(0.0f, intervalTimer-frameTime);

		if (intervalTimer == 0.0f)
		{
			Vector2 vector = {0,0};
			Vector2 targetMove = {0,0};
			switch (location)
			{
				case SpawnLocation::LEFT:
					vector = {3.0f,285.0f};
					targetMove = {80.0f,285.0f};
					break;
				case SpawnLocation::RIGHT:
					vector = {797.0f,285.0f};
					targetMove = {717.0f,285.0f};
					break;
				case SpawnLocation::UP:
					vector = {415.0f,3.0f};
					targetMove = {415.0f,73.0f};
					break;
				case SpawnLocation::DOWN:
					vector = {415.0f,597.0f};
					targetMove = {415.0f,527.0f};
					break;
			}

			Enemy* enemy;
			Item* item;
			switch (enemyType)
			{
				default:
				case EnemyType::Main:
					enemy = new Enemy(vector, GlobalVars::player);
					enemy->mode= EnemyMode::MOVETO;
					enemy->SetMoveTarget(targetMove);
					enemy->speed = 1.5f;
					enemy->diagnolSpeed = GareGames::ConvertToDiagnol(enemy->speed);
					EnemyList::AddEnemy(enemy);
					spawned++;
					break;
				case EnemyType::Tough:
					enemy = new ToughEnemy(vector, GlobalVars::player);
					enemy->hitpoints = 2.0f;
					enemy->speed = 0.5f;
					enemy->diagnolSpeed = GareGames::ConvertToDiagnol(enemy->speed);
					enemy->mode= EnemyMode::MOVETO;
					enemy->SetMoveTarget(targetMove);
					EnemyList::AddEnemy(enemy);
					spawned++;
					break;
				case EnemyType::ITEM_Cash:
					item = new Cash();
					item->textureName = "cash";
					item->position.x = GetRandomValue(50, 700);
					item->position.y = GetRandomValue(50, 500);
					ItemList::AddItem(item);
					break;
				case EnemyType::ITEM_Rifle:
					item = new RifleItem();
					item->textureName = "rifle";
					item->position.x = GetRandomValue(50, 700);
					item->position.y = GetRandomValue(50, 500);
					ItemList::AddItem(item);
					break;
			}
			intervalTimer = interval;

			if (spawned == amount) bDone = true;
		}
	}
}

Spawner::Spawner()
{
}
void Spawner::Update(float frameTime)
{
	for(SpawnJob* spawnJob : spawnJobs)
	{
		spawnJob->Update(frameTime);
	}
}
void Spawner::AddJob(EnemyType enemyType, SpawnLocation location, int amount, float startTime, float interval)
{	
	SpawnJob* spawnJob = new SpawnJob(enemyType, location, amount, startTime, interval);
	spawnJobs.push_back(spawnJob);
}
void Spawner::Start()
{
}
void Spawner::Reset()
{
	for(SpawnJob* spawnJob : spawnJobs)
	{
		spawnJob->Reset();
	}
}
