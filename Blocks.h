#pragma once
#include "SDL.h"
#include "BlockTypes.h"
#include "Vector2.h"
class Blocks
{
private:
	// Holds Position of Block on Screen
	SDL_Rect m_rectangle;
	bool isWall;

public:
	Blocks();
	~Blocks();

	void Update();
	void Init(float posX, float posY, float width, float height);
	Vector2 getPosition() const;
	Vector2 getSize() const;
};