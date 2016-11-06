#pragma once

class Vector2 {
private:
	float m_x;
	float m_y;
public:
	float x;
	float y;
	Vector2();
	Vector2(int x, int y);
	Vector2(float x, float y);
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator*=(const Vector2& other);
	Vector2 operator/(const Vector2& other);
};