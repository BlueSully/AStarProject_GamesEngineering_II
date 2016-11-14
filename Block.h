#pragma once
#include "SDL.h"
#include "BlockTypes.h"
#include "BasicTypes.h"
#include "Renderer.h"

class Block
{
private:
	// Holds Position of Block on Screen
	Rect m_rectangle;
	Colour m_colour;
	BlockType m_type;

public:
	Block();
	~Block();

	void Update();
	void Init(float posX, float posY, float width, float height, BlockType type);
	void initializeColour();
	void render(Renderer* render);

	Point2D getPosition() const;
	Size2D getSize() const;
	void setType(BlockType val);
	BlockType getType() const;
	void setColour(Colour val);

};