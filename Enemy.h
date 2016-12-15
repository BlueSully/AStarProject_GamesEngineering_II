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
	Colour m_pathColour;

	vector<NodeBlock *> m_path;
	NodeBlock * curBlock;

	int nextPathBlockValue;
	float elapsedTime;
	float TimeToMove;

	SDL_mutex* m_lock;
public:
	Enemy();
	Enemy(Point2D position, Size2D bounds, int blockIndex, Colour pColour);
	~Enemy();

	void Update(float deltatime, GameSpeed speed);
	void render(Renderer * r);

	Point2D getPosition() const;
	Size2D getBounds() const;
	int getBlockIndex() const;
	void setBlockIndex(int value);
	Colour getPathColour() const;

	NodeBlock * getNextBlock(int currentblock);
	void setPath(vector<NodeBlock*> value);
	vector<NodeBlock *> getPath() const;
	void clearPath();

};

