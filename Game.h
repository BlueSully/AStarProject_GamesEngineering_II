#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>
#include "Grid.h"
#include "Player.h"
#include "Enemy.h"
#include "Renderer.h"
#include "MovementType.h"

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

private:
	bool debug;
	bool m_running;

	Grid * m_grid;
	Player * m_player;
	vector<Enemy *> m_enemies;
	Renderer m_renderer;

	int m_enemySize;
	Size2D m_winSize;
	Size2D m_worldBounds;

	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;

	SDL_Thread *thread;
	int threadReturnValue;
};
#endif