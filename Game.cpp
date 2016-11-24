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

void Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags) 
{
	srand(static_cast<unsigned int>(time(NULL)));

	Size2D winSize(800, 600);

	//How many Blocks wide is the blocks
	float vpWidth = 30;

	//creates our renderer, which looks after drawing and the window
	m_renderer.init(winSize, "Astar Threading");
	float aspectRatio = winSize.w / winSize.h;
	
	WorldBounds = Size2D(vpWidth, vpWidth / aspectRatio);
	Point2D vpBottomLeft(-WorldBounds.w / 2, -WorldBounds.h / 2);

	//set up the viewport
	Rect vpRect(vpBottomLeft, WorldBounds);
	m_renderer.setViewPort(vpRect);

	

	m_g1.init(static_cast<int>(vpWidth), Size2D(WorldBounds.w / vpWidth, WorldBounds.h / vpWidth));

	Point2D playerPos = Point2D(m_g1.getBlockAtIndex(0).getPosition().x, m_g1.getBlockAtIndex(0).getPosition().y);
	Size2D playerSize = Size2D((WorldBounds.w / vpWidth), (WorldBounds.h / vpWidth));
	m_player = new Player(playerPos, playerSize, 0);

	m_running = true;
}

void Game::LoadContent()
{

}

void Game::Render()
{
	m_renderer.clear(Colour(0, 0, 0));
	m_g1.render(&m_renderer);
	m_player->render(&m_renderer);
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
			case SDLK_d:
				if (m_player->getBlockIndex() + WorldBounds.w > 0)
				{
					m_player->moveRight(WorldBounds, &m_g1.getBlockAtIndex(m_player->getBlockIndex()));
				}
				break;
			case SDLK_a:
				m_player->moveLeft(WorldBounds, &m_g1.getBlockList());
				break;
			case SDLK_w:
				m_player->moveUp(WorldBounds, &m_g1.getBlockList());
				break;
			case SDLK_s:
				m_player->moveDown(WorldBounds, &m_g1.getBlockList());
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