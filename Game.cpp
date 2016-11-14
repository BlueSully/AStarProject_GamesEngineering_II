#include "Game.h"
#include <iostream>
#include <thread>


using namespace std;

Game::Game() : m_running(false)
{
}

Game::~Game()
{
}

bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags) 
{
	Size2D winSize(800, 600);
	//Define some basic types needed for 2D graphics

	float vpWidth = 30;
	//creates our renderer, which looks after drawing and the window
	m_renderer.init(winSize, "Astar Threading");

	//set up the viewport
	//we want the vp centred on origin and 20 units wide
	float aspectRatio = winSize.w / winSize.h;
	Size2D vpSize(vpWidth, vpWidth / aspectRatio);
	Point2D vpBottomLeft(-vpSize.w / 2, -vpSize.h / 2);

	Rect vpRect(vpBottomLeft, vpSize);
	m_renderer.setViewPort(vpRect);

	m_running = true;

	g1.init(vpWidth, winSize);

	return true;
}

void Game::LoadContent()
{

}

void Game::Render()
{
	m_renderer.clear(Colour(0, 0, 0));
	g1.render(&m_renderer);
	m_renderer.present();
}

void Game::Update()
{

}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					m_running = false;
					break;
				case SDLK_UP:

					break;
				case SDLK_DOWN:

					break;
				case SDLK_LEFT:

					break;
				case SDLK_RIGHT:

					break;
				default:
					
					break;
				}
	}
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::UnloadContent()
{
	DEBUG_MSG("Unloading Content");

}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}