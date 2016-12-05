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
	void Reset();
	void Render();
	void Update();
	void HandleEvents();
	bool IsRunning();
	void CleanUp();
private:
	
	bool m_running;
	Grid m_g1;
	Player * m_player;
	vector<Enemy *> m_enemies;
	Renderer m_renderer;

	Size2D WorldBounds;

	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;

};
#endif