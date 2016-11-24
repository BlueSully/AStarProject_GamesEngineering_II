#pragma once

#include "SDL.h"
#include "BlockTypes.h"
#include "BasicTypes.h"
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
	int getBlockIndex() const;
	void setBlockIndex(int value);
	void moveRight(Size2D WorldBounds, Block * BlockRight);
	void moveLeft(Size2D WorldBounds, vector<Block> * blockList);
	void moveUp(Size2D WorldBounds, vector<Block> * blockList);
	void moveDown(Size2D WorldBounds, vector<Block> * blockList);
	void render(Renderer * r);
};

