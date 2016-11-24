#pragma once

#include "SDL.h"
#include "BlockTypes.h"
#include "BasicTypes.h"
#include "MovementType.h"
#include "Renderer.h"
#include "Block.h"

class Player
{
private:
	int m_blockIndex;
	Rect m_rectangle;
	Colour m_colour;

public:
	Player();
	Player(Point2D position, Size2D bounds, int blockIndex);
	~Player();

	void update();
	Point2D getPosition() const;
	Size2D getBounds() const;
	int getBlockIndex() const;
	void setBlockIndex(int value);
	void move(MovementDirection moveDir);
	void render(Renderer * r);
};

