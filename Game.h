#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>
#include "Grid.h"
#include "Renderer.h"

class Game
{
public:
	Game();
	~Game();
	bool Initialize(const char*, int, int, int, int, int);
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
	Grid g1;

	Renderer m_renderer;

	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;

};
#endif