#include "Vector2.h"

Vector2::Vector2() : m_x(0), m_y(0)
{
	
}

Vector2::Vector2(int x, int y) : m_x(x), m_y(x)
{

}

Vector2::Vector2(float x, float y) : m_x(x), m_y(y)
{

}

Vector2 Vector2::operator+=(const Vector2& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	return Vector2(m_x, m_y);
}

Vector2 Vector2::operator-=(const Vector2& other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;
	return Vector2(m_x, m_y);
}

Vector2 Vector2::operator*=(const Vector2& other)
{
	m_x *= other.m_x;
	m_y *= other.m_y;
	return Vector2(m_x, m_y);
}

Vector2 Vector2::operator/(const Vector2& other)
{
	m_x = m_x / other.m_x;
	m_y = m_y / other.m_y;
	return Vector2(m_x, m_y);
}