#pragma once
#include "SDL.h"
#include "BlockTypes.h"
#include "BasicTypes.h"
#include "Renderer.h"

class NodeBlock
{
private:
	// Holds Position of Block on Screen
	Rect m_rectangle;
	Colour m_colour;
	BlockType m_type;
	int m_currentIndex;
	int m_topBlockIndex;
	int m_bottomBlockIndex;
	int m_rightBlockIndex;
	int m_leftBlockIndex;

public:
	NodeBlock();
	~NodeBlock();

	void Update();
	void Init(float posX, float posY, float width, float height, BlockType type);
	void initializeColour();
	void render(Renderer* render);

	Point2D getPosition() const;
	Size2D getSize() const;
	void setType(BlockType val);
	BlockType getType() const;
	void setColour(Colour val);

	void setNeighbours(int gridSize, int currentIndex);
};