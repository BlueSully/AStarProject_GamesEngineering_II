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

static int TestThread(void *ptr)
{
	int cnt;

	for (cnt = 0; cnt < 30; ++cnt) 
	{
		printf("\nThread counter: %d", cnt);
		SDL_Delay(150);
	}

	return cnt;
}

void Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags) 
{
	DEBUG_MSG("Game Init Called");
	srand(static_cast<unsigned int>(time(NULL)));

	m_winSize = Size2D(static_cast<float>(width), static_cast<float>(height));
	
	//Creates our renderer, which looks after drawing and the window
	m_renderer.init(m_winSize, "Astar Threading");
	float aspectRatio = m_winSize.w / m_winSize.h;
	
	//How many Blocks wide is the blocks
	float vpWidth = 30;
	m_worldBounds = Size2D(vpWidth, vpWidth / aspectRatio);
	Point2D vpBottomLeft(-m_worldBounds.w / 2, -m_worldBounds.h / 2);

	//Set up the viewport
	Rect vpRect(vpBottomLeft, m_worldBounds);
	m_renderer.setViewPort(vpRect);

	//Setup Grid
	m_grid = new Grid(static_cast<int>(vpWidth), Size2D(m_worldBounds.w / vpWidth, m_worldBounds.h / vpWidth));

	if (m_grid != nullptr)
	{
		//Setup Player
		int playerBlockIndex = static_cast<int>(((vpWidth / 2)) * (vpWidth / 3) * 5);

		Point2D playerPos = Point2D(m_grid->getBlockAtIndex(playerBlockIndex).getPosition().x, m_grid->getBlockAtIndex(playerBlockIndex).getPosition().y);
		Size2D playerSize = Size2D((m_worldBounds.w / vpWidth), (m_worldBounds.h / vpWidth));
		m_player = new Player(playerPos, playerSize, playerBlockIndex);

		m_enemySize = 1;
		//Setup Enemies
		for (int i = 0; i < m_enemySize; i++)
		{
			int blockIndex = (m_grid->getGridSize() * m_grid->getGridSize()) - (5 + (2 * i));
			Point2D enemyPos = Point2D(m_grid->getBlockAtIndex(blockIndex).getPosition().x, m_grid->getBlockAtIndex(blockIndex).getPosition().y);
			Size2D enemySize = Size2D((m_worldBounds.w / vpWidth), (m_worldBounds.h / vpWidth));
			m_enemies.push_back(new Enemy(enemyPos, enemySize, blockIndex));
		}
	}
	
	m_running = true;

	//printf("\nSimple SDL_CreateThread test:");
	//// Simply create a thread
	//thread = SDL_CreateThread(TestThread, "TestThread", (void *)NULL);

	//if (NULL == thread)
	//{
	//	printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	//}
}

void Game::LoadContent()
{

}

void Game::Render()
{
	m_renderer.clear(Colour(0, 0, 0));

	if (m_grid != nullptr)
	{
		//Drawing Grid
		m_grid->render(&m_renderer);

		//Drawing Player
		m_player->render(&m_renderer);

		//Drawing Enemies
		for (size_t i = 0; i < 5; i++)
		{
			m_enemies[0]->render(&m_renderer);
		}
	}

	m_renderer.present();
}

void Game::Reset(int gridSize, int enemysize)
{
	cout << "Reset Called" << endl;
	//Clearing Memory
	delete m_grid;

	delete m_player;

	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}

	m_enemies.clear();

	//reinitializing window
	float aspectRatio = m_winSize.w / m_winSize.h;
	m_worldBounds = Size2D(static_cast<float>(gridSize), static_cast<float>(gridSize / aspectRatio));
	Point2D vpBottomLeft(-m_worldBounds.w / 2, -m_worldBounds.h / 2);

	//Set up the viewport
	Rect vpRect(vpBottomLeft, m_worldBounds);
	m_renderer.setViewPort(vpRect);

	//reinitializing objects
	m_grid = new Grid(static_cast<int>(gridSize), Size2D(m_worldBounds.w / gridSize, m_worldBounds.h / gridSize));

	if (m_grid != nullptr)
	{
		//Setup Player
		int playerBlockIndex = static_cast<int>(((gridSize / 2)) * (gridSize / 3) * 5);

		Point2D playerPos = Point2D(m_grid->getBlockAtIndex(playerBlockIndex).getPosition().x, m_grid->getBlockAtIndex(playerBlockIndex).getPosition().y);
		Size2D playerSize = Size2D((m_worldBounds.w / gridSize), (m_worldBounds.h / gridSize));
		m_player = new Player(playerPos, playerSize, playerBlockIndex);

		m_enemySize = enemysize;
		//Setup Enemies
		for (int i = 0; i < m_enemySize; i++)
		{
			int blockIndex = (m_grid->getGridSize() * m_grid->getGridSize()) - (5 + (2 * i));
			Point2D enemyPos = Point2D(m_grid->getBlockAtIndex(blockIndex).getPosition().x, m_grid->getBlockAtIndex(blockIndex).getPosition().y);
			Size2D enemySize = Size2D((m_worldBounds.w / gridSize), (m_worldBounds.h / gridSize));
			m_enemies.push_back(new Enemy(enemyPos, enemySize, blockIndex));
		}
	}
}

void Game::Update(float deltaTime)
{
	if (m_grid->isGridInitialised() && m_grid != nullptr && !debug)
	{
		m_grid->resetGrid();
		vector<NodeBlock> path = m_grid->oldAStarAlgorithm(&m_grid->getBlockAtIndex(m_enemies[0]->getBlockIndex()), &m_grid->getBlockAtIndex(m_player->getBlockIndex()));
		debug = true;
	}
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
				if (m_player->getPosition().x + m_player->getBounds().w < m_worldBounds.w &&
					m_grid->getBlockAtIndex(m_player->getBlockIndex() + m_grid->getGridSize()).getType() != BlockType::WALL)
				{
					//can move right and Update
					m_player->move(MovementDirection::MOVE_RIGHT);
					m_player->setBlockIndex(m_player->getBlockIndex() + m_grid->getGridSize());
				}
				break;
			case SDLK_a:
				if (m_player->getPosition().x > 0 &&
					m_grid->getBlockAtIndex(m_player->getBlockIndex() - m_grid->getGridSize()).getType() != BlockType::WALL)
				{
					//can move Left and Update
					m_player->move(MovementDirection::MOVE_LEFT);
					m_player->setBlockIndex(m_player->getBlockIndex() - m_grid->getGridSize());
				}
				break;
			case SDLK_w:
				if (m_player->getPosition().y + m_player->getBounds().h > m_player->getBounds().h &&
					m_grid->getBlockAtIndex(m_player->getBlockIndex() - 1).getType() != BlockType::WALL)
				{
					//can move Up and Update
					m_player->move(MovementDirection::MOVE_UP);
					m_player->setBlockIndex(m_player->getBlockIndex() - 1);
				}
				break;
			case SDLK_s:
				if (m_player->getPosition().y < m_worldBounds.h - m_player->getBounds().h &&
					m_grid->getBlockAtIndex(m_player->getBlockIndex() + 1).getType() != BlockType::WALL)
				{
					//can move down and Update
					m_player->move(MovementDirection::MOVE_DOWN);
					m_player->setBlockIndex(m_player->getBlockIndex() + 1);
				}
				break;
			case SDLK_x:
				debug = false;
				break;
				
				//Changing Grid //Resetting grid with block and enemies 
			case SDLK_1:
				Reset(30, 1);
				break;
			case SDLK_2:
				Reset(100, 1);
				break;
			case SDLK_3:
				Reset(1000, 1);
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
	//SDL_KillThread(thread);

	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}