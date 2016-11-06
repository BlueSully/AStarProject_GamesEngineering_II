#pragma once
#include "SDL.h"
#include "BlockTypes.h"
#include "Vector2.h"

class Block
{
private:
	// Holds Position of Block on Screen
	SDL_Rect m_rectangle;
	SDL_Colour m_colour;
	bool m_isWall;
	BlockType m_type;

public:
	Block();
	~Block();

	void Update();
	void Init(float posX, float posY, float width, float height, int type);
	void initializeColour();
	Vector2 getPosition() const;
	Vector2 getSize() const;
	bool isBlockWall() const;
	void render(SDL_Renderer* render);
};