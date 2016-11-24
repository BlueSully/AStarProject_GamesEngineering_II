#include "Player.h"


Player::Player() : m_blockIndex(0)
{
	m_rectangle.pos.x = 0;
	m_rectangle.pos.y = 0;
	m_rectangle.size.w = 1;
	m_rectangle.size.h = 1;
	m_colour = { 255, 0, 0, 255 };
}

Player::Player(Point2D position, Size2D bounds, int blockIndex) : m_blockIndex(blockIndex)
{
	m_rectangle.pos.x = position.x;
	m_rectangle.pos.y = position.y;
	m_rectangle.size.w = bounds.w;
	m_rectangle.size.h = bounds.h;
	m_colour = { 255, 0, 0, 255 };
}

Player::~Player()
{

}

void Player::update()
{

}

Point2D Player::getPosition() const
{
	return m_rectangle.pos;
}

Size2D Player::getBounds() const
{
	return m_rectangle.size;
}

int Player::getBlockIndex() const
{
	return m_blockIndex;
}

void Player::setBlockIndex(int value)
{
	m_blockIndex = value;
}

void Player::move(MovementDirection moveDir)
{
	if (moveDir == MovementDirection::MOVE_RIGHT) 
	{
		m_rectangle.pos.x += m_rectangle.size.w;
	}
	else if (moveDir == MovementDirection::MOVE_LEFT)
	{
		m_rectangle.pos.x -= m_rectangle.size.w;
	}
	else if (moveDir == MovementDirection::MOVE_DOWN)
	{
		m_rectangle.pos.y += m_rectangle.size.h;
	}
	else if (moveDir == MovementDirection::MOVE_UP)
	{
		m_rectangle.pos.y -= m_rectangle.size.h;
	}
}

void Player::render(Renderer * r)
{
	r->drawWorldFillRect(m_rectangle, m_colour);
}