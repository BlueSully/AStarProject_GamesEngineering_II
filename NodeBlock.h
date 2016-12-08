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
	Colour m_originalColour;
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
	void Init(float posX, float posY, float width, float height, BlockType type, int index);
	void initializeColour();
	void render(Renderer* render);

	int getIndex() const;
	Point2D getPosition() const;
	Size2D getSize() const;
	void setType(BlockType val);	
	BlockType getType() const;
	void Reset();
	void setOriginalColour(Colour val);
	void setSolidColour(Colour val);
	void setColour(Colour val);
	void setMarked(bool value);

	void setNeighbours(int gridSize, int currentIndex);
	int getTopNeighbour() const;
	int getBottomNeighbour() const;
	int getLeftNeighbour() const;
	int getRightNeighbour() const;

};