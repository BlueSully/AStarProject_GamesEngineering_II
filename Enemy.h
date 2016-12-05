#pragma once

#include "SDL.h"
#include "BlockTypes.h"
#include "BasicTypes.h"
#include "MovementType.h"
#include "Renderer.h"
#include "NodeBlock.h"

class Enemy
{
private:
	int m_blockIndex;
	Rect m_rectangle;
	Colour m_colour;
	vector<NodeBlock *> m_openList;
	vector<NodeBlock *> m_closeList;
	vector<NodeBlock *> m_path;
public:
	Enemy();
	Enemy(Point2D position, Size2D bounds, int blockIndex);
	~Enemy();

	void update();
	void render(Renderer * r);

	Point2D getPosition() const;
	Size2D getBounds() const;
	vector<NodeBlock *> getOpenList();
	vector<NodeBlock *> getClosedList();
};

