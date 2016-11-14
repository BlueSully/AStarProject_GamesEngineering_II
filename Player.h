#pragma once

#include "SDL.h"
#include "BlockTypes.h"
#include "BasicTypes.h"
#include "Renderer.h"

class Player
{
private:
	Rect m_rectangle;
	Colour m_colour;

public:
	Player();
	~Player();
};

