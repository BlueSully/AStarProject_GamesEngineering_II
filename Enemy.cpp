#include "Enemy.h"

Enemy::Enemy() : m_blockIndex(0), calculateNewPath(true)
{
	m_rectangle.pos.x = 0;
	m_rectangle.pos.y = 0;
	m_rectangle.size.w = 1;
	m_rectangle.size.h = 1;
	m_colour = { 255, 0, 0, 255 };
}

Enemy::Enemy(Point2D position, Size2D bounds, int blockIndex) : m_blockIndex(blockIndex), calculateNewPath(true)
{
	m_rectangle.pos.x = position.x;
	m_rectangle.pos.y = position.y;
	m_rectangle.size.w = bounds.w;
	m_rectangle.size.h = bounds.h;
	m_colour = { 50, 0, 255, 255 };
}

Enemy::~Enemy()
{

}

void Enemy::update()
{

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

bool Enemy::getFoundPath() const
{
	return foundPath;
}

void Enemy::setFoundPath(bool value)
{
	foundPath = value;
}

bool Enemy::getCalculateNewPath() const
{
	return calculateNewPath;
}

void Enemy::setCalculateNewPath(bool value)
{
	calculateNewPath = value;
}

void Enemy::setPath(vector<NodeBlock*> value)
{
	m_path.clear();
	m_path = value;
}

vector<NodeBlock*> Enemy::getPath() const
{
	return m_path;
}

void Enemy::clearPath()
{
	m_path.clear();
}

void Enemy::render(Renderer * r)
{
	r->drawWorldFillRect(m_rectangle, m_colour);
}
