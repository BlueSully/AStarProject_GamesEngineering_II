#pragma once
#define SDL_MAIN_HANDLED
#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "SDL.h"
#include "SDL_image.h"
#endif

#include <vector>
#include "BasicTypes.h"

using namespace std;


//Responsible for all drawing operations
//abstracts away specfic SDL specific drawing functions
class Renderer{

	// size of window in pixels
	Size2D windowSize;
	//position of window in world coordinates
	//change these if you want to zoom or pan
	Point2D viewportBottomLeft;
	Size2D viewportSize;
	SDL_Window *window;
	SDL_Renderer *sdl_renderer;
	vector<SDL_Texture*> textures;

public:
	Renderer();
	~Renderer();
	bool init(const Size2D&, const char*);
	void destroy();
	void drawRect(const Rect&, const Colour&) const;
	void drawFillRect(const Rect&, const Colour&) const;
	void drawWorldRect(const Rect&, const Colour&) const;
	void drawWorldFillRect(const Rect&, const Colour&) const;

	void drawTexture(int textureName, const Rect& r) const;
	void drawTexture(int textureName, const Rect& r, double angle) const;
	void present();
	void clear(const Colour&) const;
	Point2D worldToScreen(const Point2D&) const;
	Rect worldToScreen(const Rect&) const;
	void setViewPort(const Rect&);
	Size2D getWindowSize() const;
};

