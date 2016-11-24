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

	//SetupGrid
	m_g1.init(static_cast<int>(vpWidth), Size2D(WorldBounds.w / vpWidth, WorldBounds.h / vpWidth));

	//Setup Player
	Point2D playerPos = Point2D(m_g1.getBlockAtIndex(0).getPosition().x, m_g1.getBlockAtIndex(0).getPosition().y);
	Size2D playerSize = Size2D((WorldBounds.w / vpWidth), (WorldBounds.h / vpWidth));
	m_player = new Player(playerPos, playerSize, 0);

	//Setup Enemies
	for (size_t i = 0; i < 5; i++)
	{
		int blockIndex = (m_g1.getGridSize() * m_g1.getGridSize()) - (5 + (2 * i));
		Point2D enemyPos = Point2D(m_g1.getBlockAtIndex(blockIndex).getPosition().x, m_g1.getBlockAtIndex(blockIndex).getPosition().y);
		Size2D enemySize = Size2D((WorldBounds.w / vpWidth), (WorldBounds.h / vpWidth));
		m_enemies.push_back(new Enemy(enemyPos, enemySize, blockIndex));
	}

	m_running = true;
}

void Game::LoadContent()
{

}

void Game::Render()
{
	m_renderer.clear(Colour(0, 0, 0));
	//Drawing Grid
	m_g1.render(&m_renderer);

	//Drawing Player
	m_player->render(&m_renderer);

	//Drawing Enemies
	for (size_t i = 0; i < 5; i++)
	{
		m_enemies[i]->render(&m_renderer);
	}

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
			// Handling Player Movement
			case SDLK_d:
				if (m_player->getPosition().x + m_player->getBounds().w < WorldBounds.w &&
					m_g1.getBlockAtIndex(m_player->getBlockIndex() + m_g1.getGridSize()).getType() != BlockType::WALL)
				{
					//can move right and Update
					m_player->move(MovementDirection::MOVE_RIGHT);
					m_player->setBlockIndex(m_player->getBlockIndex() + m_g1.getGridSize());
				}
				break;
			case SDLK_a:
				if (m_player->getPosition().x > 0 &&
					m_g1.getBlockAtIndex(m_player->getBlockIndex() - m_g1.getGridSize()).getType() != BlockType::WALL)
				{
					//can move Left and Update
					m_player->move(MovementDirection::MOVE_LEFT);
					m_player->setBlockIndex(m_player->getBlockIndex() - m_g1.getGridSize());
				}
				break;
			case SDLK_w:
				if (m_player->getPosition().y + m_player->getBounds().h > m_player->getBounds().h &&
					m_g1.getBlockAtIndex(m_player->getBlockIndex() - 1).getType() != BlockType::WALL)
				{
					//can move Up and Update
					m_player->move(MovementDirection::MOVE_UP);
					m_player->setBlockIndex(m_player->getBlockIndex() - 1);
				}
				break;
			case SDLK_s:
				if (m_player->getPosition().y < WorldBounds.h - m_player->getBounds().h &&
					m_g1.getBlockAtIndex(m_player->getBlockIndex() + 1).getType() != BlockType::WALL)
				{
					//can move down and Update
					m_player->move(MovementDirection::MOVE_DOWN);
					m_player->setBlockIndex(m_player->getBlockIndex() + 1);
				}
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