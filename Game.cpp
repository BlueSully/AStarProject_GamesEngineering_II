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
	srand(static_cast<unsigned int>(time(NULL)));

	Size2D winSize(800, 600);

	//How many Blocks wide is the blocks
	float vpWidth = 30;

	//creates our renderer, which looks after drawing and the window
	m_renderer.init(winSize, "Astar Threading");


	float aspectRatio = winSize.w / winSize.h;
	Size2D vpSize(vpWidth, vpWidth / aspectRatio);
	Point2D vpBottomLeft(-vpSize.w / 2, -vpSize.h / 2);

	//set up the viewport
	Rect vpRect(vpBottomLeft, vpSize);
	m_renderer.setViewPort(vpRect);

	m_running = true;

	g1.init(static_cast<int>(vpWidth), vpSize);

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

void Game::Reset()
{
	cout << "Reset Called" << endl;
}

void Game::Update()
{

}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_running = false;
				break;
			case SDLK_r:
				
				break;
			default:

				break;
			}
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_running = false;
				break;
			case SDLK_r:
		
				break;
			default:

				break;
			}
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