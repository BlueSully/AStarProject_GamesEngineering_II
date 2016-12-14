#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>
#include <time.h>   
#include "Grid.h"
#include "Player.h"
#include "Enemy.h"
#include "Renderer.h"
#include "MovementType.h"
#include "ThreadPool.h"

class Game
{
public:
	Game();
	~Game();

	void Initialize(const char*, int, int, int, int, int);
	void LoadContent();
	void UnloadContent();
	void Reset(int gridSize, int enemysize);
	void Render();
	void Update(float deltaTime);
	void HandleEvents();
	bool IsRunning();
	void CleanUp();


	void runAstar(int enemyIndex);

	Grid * getGrid() const 
	{
		return m_grid;
	}
	Player * getPlayer() const
	{
		return m_player;
	}
	vector<Enemy *> getEnemies() const
	{
		return m_enemies;
	}
	SDL_mutex * getMutex() const 
	{
		return mutex;
	}

private:
	bool debug;
	bool playerOnSameBlock;
	
	bool m_running;

	Grid * m_grid;
	Player * m_player;
	vector<Enemy *> m_enemies;
	Renderer m_renderer;

	int lastPlayerBlock;
	int m_enemySize;
	Size2D m_winSize;
	Size2D m_worldBounds;

	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;

	ThreadPool * m_threadPool;
	int maxNumThreads;
	vector<SDL_Thread *> threadingQueue;
	SDL_mutex * mutex;
};
#endif