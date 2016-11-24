#include "Enemy.h"

Enemy::Enemy() : m_blockIndex(0)
{
	m_rectangle.pos.x = 0;
	m_rectangle.pos.y = 0;
	m_rectangle.size.w = 1;
	m_rectangle.size.h = 1;
	m_colour = { 255, 0, 0, 255 };
}

Enemy::Enemy(Point2D position, Size2D bounds, int blockIndex) : m_blockIndex(blockIndex)
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

void Enemy::render(Renderer * r)
{
	r->drawWorldFillRect(m_rectangle, m_colour);
}
