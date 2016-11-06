#include "Vector2.h"

Vector2::Vector2() : m_x(0), m_y(0)
{
	x = m_x;
	y = m_y;
}

Vector2::Vector2(int xVal, int yVal) : m_x(static_cast<float>(xVal)), m_y(static_cast<float>(yVal))
{
	x = static_cast<int>(m_x);
	y = static_cast<int>(m_y);
}

Vector2::Vector2(float xVal, float yVal) : m_x(xVal), m_y(yVal)
{
	x = m_x;
	y = m_y;
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