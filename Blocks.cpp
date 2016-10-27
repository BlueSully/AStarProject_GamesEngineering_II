#include "Blocks.h"

Blocks::Blocks()
{

}

void Blocks::Update()
{
}

void Blocks::Init(float posX, float posY, float width, float height)
{
	m_rectangle.x = static_cast<int>(posX);
	m_rectangle.y = static_cast<int>(posY);
	m_rectangle.w = static_cast<int>(width);
	m_rectangle.h = static_cast<int>(height);
}

Vector2 Blocks::getPosition() const
{
	return Vector2(m_rectangle.x, m_rectangle.y);
}
Vector2 Blocks::getSize() const
{
	return Vector2(m_rectangle.w, m_rectangle.h);
}

Blocks::~Blocks()
{

}
