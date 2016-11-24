#pragma once

#include "SDL.h"
#include "BlockTypes.h"
#include "BasicTypes.h"
#include "MovementType.h"
#include "Renderer.h"
#include "Block.h"

class Enemy
{
private:
	int m_blockIndex;
	Rect m_rectangle;
	Colour m_colour;

public:
	Enemy();
	Enemy(Point2D position, Size2D bounds, int blockIndex);
	~Enemy();

	void update();
	Point2D getPosition() const;
	Size2D getBounds() const;
	void render(Renderer * r);
};

