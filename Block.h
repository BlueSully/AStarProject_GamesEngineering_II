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
	bool m_isWall;
	BlockType m_type;

public:
	Block();
	~Block();

	void Update();
	void Init(float posX, float posY, float width, float height, int type);
	void initializeColour();
	Point2D getPosition() const;
	Size2D getSize() const;
	bool isBlockWall() const;
	void render(Renderer* render);
};