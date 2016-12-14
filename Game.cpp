#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : m_running(false), playerOnSameBlock(true)
{

}

Game::~Game()
{

}

int Game::runAstar(void *ptr)
{
	
	std::pair<Game *, int> * dataPointer = static_cast<std::pair<Game *, int> *>(ptr);
	Game * gamePointer = dataPointer->first;
	int currentEnemyIndex = dataPointer->second;

	//Work on a SDL_COND to only signal this code when it is needed
	bool running = true;
	while (running)
	{
		if (gamePointer->getEnemies()[currentEnemyIndex]->getCalculateNewPath())
		{
			//printf("Thread %d called \n", currentEnemyIndex);

			//Do A*
			gamePointer->getEnemies()[currentEnemyIndex]->setPath(gamePointer->getGrid()->oldAStarAlgorithm(&gamePointer->getGrid()->getBlockAtIndex(gamePointer->getEnemies()[currentEnemyIndex]->getBlockIndex()),
																											&gamePointer->getGrid()->getBlockAtIndex(gamePointer->getPlayer()->getBlockIndex())));
			//Found Path
			gamePointer->getEnemies()[currentEnemyIndex]->setFoundPath(true);
			gamePointer->getEnemies()[currentEnemyIndex]->setCalculateNewPath(false);

			if (SDL_LockMutex(gamePointer->getMutex()) == 0)
			{
				int size = gamePointer->getEnemies()[currentEnemyIndex]->getPath().size();
				if (size > 0)
				{
					for (size_t j = 0; j < size; j++)
					{
						gamePointer->getEnemies()[currentEnemyIndex]->getPath()[j]->setColour(gamePointer->getEnemies()[currentEnemyIndex]->getPathColour());
					}
				}
				//running = false;
				SDL_UnlockMutex(gamePointer->getMutex());
			}
		}
	}

	return currentEnemyIndex;
}

void Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags) 
{
	maxNumThreads = std::thread::hardware_concurrency();
	DEBUG_MSG("Game Init Called");
	srand(static_cast<unsigned int>(time(NULL)));

	mutex = SDL_CreateMutex();
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
		int playerBlockIndex = static_cast<int>(vpWidth - 1);
		lastPlayerBlock = playerBlockIndex;
		Point2D playerPos = Point2D(m_grid->getBlockAtIndex(playerBlockIndex).getPosition().x, m_grid->getBlockAtIndex(playerBlockIndex).getPosition().y);
		Size2D playerSize = Size2D((m_worldBounds.w / vpWidth), (m_worldBounds.h / vpWidth));
		m_player = new Player(playerPos, playerSize, playerBlockIndex);

		m_enemySize = 5;
		//Setup Enemies
		for (int i = 0; i < m_enemySize; i++)
		{
			int blockIndex = (m_grid->getGridSize() * m_grid->getGridSize()) - (5 + (2 * i));
			Point2D enemyPos = Point2D(m_grid->getBlockAtIndex(blockIndex).getPosition().x, m_grid->getBlockAtIndex(blockIndex).getPosition().y);
			Size2D enemySize = Size2D((m_worldBounds.w / vpWidth), (m_worldBounds.h / vpWidth));

			m_enemies.push_back(new Enemy(enemyPos, enemySize, blockIndex, Colour(rand() % 255, rand() % 255, 0)));

			int maxThreads;
			if (maxNumThreads > 5) {
				maxThreads = 5;
			}
			if (m_grid->isGridInitialised() && threadingQueue.size() < maxThreads)
			{
				std::pair<Game *, int> astarPair = make_pair(this, i);
				threadingQueue.push_back(SDL_CreateThread(&Game::runAstar, "WorkerThread:" + i, &astarPair));
			}
		}
	}
	
	
	m_running = true;
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
		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->render(&m_renderer);
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

			m_enemies.push_back(new Enemy(enemyPos, enemySize, blockIndex, Colour(rand() % 255, rand() % 255, rand() % 255)));
		}
	}
}

void Game::Update(float deltaTime)
{
	//printf("threadSize %d\n", threadingQueue.size());
	if (m_grid->isGridInitialised() && m_grid != nullptr)
	{		
		int playerIndex = m_player->getBlockIndex();
		if (m_player->getBlockIndex() != lastPlayerBlock)
		{
			playerOnSameBlock = false;
			m_grid->resetGrid();
		}
		else
		{
			playerOnSameBlock = true;
		}

		for (size_t i = 0; i < m_enemies.size(); i++)
		{				
			if (!playerOnSameBlock && m_enemies[i]->getCalculateNewPath() == false)
			{				
				m_enemies[i]->setCalculateNewPath(true);
				lastPlayerBlock = m_player->getBlockIndex();
			}

			m_enemies[i]->Update(deltaTime, GameSpeed::FAST);
		}	
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
					playerOnSameBlock = false;
				}
				break;
			case SDLK_a:
				if (m_player->getPosition().x > 0 &&
					m_grid->getBlockAtIndex(m_player->getBlockIndex() - m_grid->getGridSize()).getType() != BlockType::WALL)
				{
					//can move Left and Update
					m_player->move(MovementDirection::MOVE_LEFT);
					m_player->setBlockIndex(m_player->getBlockIndex() - m_grid->getGridSize());
					playerOnSameBlock = false;
				}
				break;
			case SDLK_w:
				if (m_player->getPosition().y + m_player->getBounds().h > m_player->getBounds().h &&
					m_grid->getBlockAtIndex(m_player->getBlockIndex() - 1).getType() != BlockType::WALL)
				{
					//can move Up and Update
					m_player->move(MovementDirection::MOVE_UP);
					m_player->setBlockIndex(m_player->getBlockIndex() - 1);
					playerOnSameBlock = false;
				}
				break;
			case SDLK_s:
				if (m_player->getPosition().y < m_worldBounds.h - m_player->getBounds().h &&
					m_grid->getBlockAtIndex(m_player->getBlockIndex() + 1).getType() != BlockType::WALL)
				{
					//can move down and Update
					m_player->move(MovementDirection::MOVE_DOWN);
					m_player->setBlockIndex(m_player->getBlockIndex() + 1);
					playerOnSameBlock = false;
				}
				break;
			case SDLK_x:
				debug = false;
				break;
				
				//Changing Grid //Resetting grid with block and enemies 
			case SDLK_1:
				Reset(30, 2);
				break;
			case SDLK_2:
				Reset(100, 2);
				break;
			case SDLK_3:
				Reset(1000, 2);
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

	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}