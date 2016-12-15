#include "Enemy.h"

Enemy::Enemy() : m_blockIndex(0), m_lock(SDL_CreateMutex())
{
	m_rectangle.pos.x = 0;
	m_rectangle.pos.y = 0;
	m_rectangle.size.w = 1;
	m_rectangle.size.h = 1;
	m_colour = { 255, 0, 0, 255 };
	elapsedTime = 0;
}

Enemy::Enemy(Point2D position, Size2D bounds, int blockIndex, Colour pColour) : m_blockIndex(blockIndex), m_lock(SDL_CreateMutex())
{
	m_rectangle.pos.x = position.x;
	m_rectangle.pos.y = position.y;
	m_rectangle.size.w = bounds.w;
	m_rectangle.size.h = bounds.h;
	m_colour = { 50, 0, 255, 255 };
	m_pathColour = pColour;
	elapsedTime = 0;
}

Enemy::~Enemy()
{
	SDL_DestroyMutex(m_lock);
}

void Enemy::Update(float deltatime, GameSpeed speed)
{
	elapsedTime += deltatime;

	if (speed == GameSpeed::SLOW)
	{
		TimeToMove = 500;
	}
	else if (speed == GameSpeed::NORMAL)
	{
		TimeToMove = 100;
	}
	else if (speed == GameSpeed::FAST)
	{
		TimeToMove = 50;
	}
	if (SDL_LockMutex(m_lock) == 0) {
		if (m_path.size() > 0 && elapsedTime > TimeToMove)
		{
			nextPathBlockValue++;
			NodeBlock * nextBlock = getNextBlock(nextPathBlockValue);
			if (nextBlock != nullptr)
			{
				curBlock = nextBlock;
				m_rectangle.pos.x = curBlock->getPosition().x;
				m_rectangle.pos.y = curBlock->getPosition().y;
				m_blockIndex = nextBlock->getIndex();
			}
			elapsedTime = 0;
		}
		SDL_UnlockMutex(m_lock);
	}
}

NodeBlock * Enemy::getNextBlock(int currentblock)
{
	int value = (m_path.size() - currentblock) - 1;
	if (!(value < 0))
		return m_path[value];
	else
		return nullptr;
}

Point2D Enemy::getPosition() const
{
	return m_rectangle.pos;
}

Size2D Enemy::getBounds() const
{
	return m_rectangle.size;
}

int Enemy::getBlockIndex() const
{
	return m_blockIndex;
}

void Enemy::setBlockIndex(int value)
{
	m_blockIndex = value;
}

Colour Enemy::getPathColour() const
{
	return m_pathColour;
}

void Enemy::setPath(vector<NodeBlock*> value)
{
	nextPathBlockValue = 0;
	m_path.clear();
	m_path = value;
}

vector<NodeBlock*> Enemy::getPath() const
{
	return m_path;
}

void Enemy::clearPath()
{
	nextPathBlockValue = 0;
	m_path.clear();
}

void Enemy::render(Renderer * r)
{
	r->drawWorldFillRect(m_rectangle, m_colour);
}
