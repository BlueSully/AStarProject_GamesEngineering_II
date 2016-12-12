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
	vector<NodeBlock *> m_path;
	bool foundPath;
	bool calculateNewPath;
public:
	Enemy();
	Enemy(Point2D position, Size2D bounds, int blockIndex);
	~Enemy();

	void update();
	void render(Renderer * r);

	Point2D getPosition() const;
	Size2D getBounds() const;
	int getBlockIndex() const;
	void setBlockIndex(int value);
	bool getFoundPath() const;
	void setFoundPath(bool value);
	bool getCalculateNewPath() const;
	void setCalculateNewPath(bool value);

	void Enemy::setPath(vector<NodeBlock*> value);
	vector<NodeBlock *> getPath() const;
	void clearPath();

};

