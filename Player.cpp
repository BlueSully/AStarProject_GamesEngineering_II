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

int Player::getBlockIndex() const
{
	return m_blockIndex;
}

void Player::setBlockIndex(int value)
{
	m_blockIndex = value;
}


void Player::moveRight(Size2D WorldBounds, Block * BlockRight)
{
	if ((m_rectangle.pos.x + m_rectangle.size.w < WorldBounds.w) && BlockRight->getType() != BlockType::WALL)
	{
		//can move right
		m_rectangle.pos.x += m_rectangle.size.w;
		m_blockIndex = m_blockIndex + 10;
	}
}

void Player::moveLeft(Size2D WorldBounds, vector<Block> * blockList)
{
	if (m_blockIndex - 10 > 0)
	{
		if (m_rectangle.pos.x > 0 && blockList->at(m_blockIndex - 10).getType() != BlockType::WALL)
		{
			//can move Left
			m_rectangle.pos.x -= m_rectangle.size.w;
			m_blockIndex = m_blockIndex - 10;
		}
	}
}

void Player::moveUp(Size2D WorldBounds, vector<Block> * blockList)
{
	if (m_rectangle.pos.y > 0)
	{
		//can move Up
		m_rectangle.pos.y -= m_rectangle.size.h;
	}
}

void Player::moveDown(Size2D WorldBounds, vector<Block> * blockList)
{
	if (m_rectangle.pos.y + m_rectangle.size.h < WorldBounds.h)
	{
		//can move Down
		m_rectangle.pos.y += m_rectangle.size.h;
	}
}

void Player::render(Renderer * r)
{
	r->drawWorldFillRect(m_rectangle, m_colour);
}