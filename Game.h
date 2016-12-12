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
#include "SDL_thread.h"
#include "SDL_timer.h"
#include <iostream>


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

	static int runAstar(void *ptr);

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

	vector<SDL_Thread *> threadingQueue;
	SDL_mutex *mutex;
};
#endif