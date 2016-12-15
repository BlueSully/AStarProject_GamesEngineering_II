
#include <iostream>
using namespace std;
#define SDL_MAIN_HANDLED

#ifdef __APPLE__
    #include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
    #include "SDL.h"
#endif

#include "Renderer.h"

Renderer::Renderer() : sdl_renderer(NULL)
{
	
}

bool Renderer::init(const Size2D& winSize, const char* title) 
{
	int e = SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2
	windowSize = winSize;
	if (e != 0) 
	{
		// problem with SDL?...
		cout << "Could not init SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		title,							    // window title
		SDL_WINDOWPOS_UNDEFINED,			// initial x position
		SDL_WINDOWPOS_UNDEFINED,			// initial y position
		(int)winSize.w,						// width, in pixels
		(int)winSize.h,						// height, in pixels
		SDL_WINDOW_OPENGL					// flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) 
	{
		// In the case that the window could not be made...
		cout << "Could not create window: " << SDL_GetError() << std::endl;
		return false;
	}

	sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == NULL)
	{
		// In the case that the renderer could not be made...
		cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

//draw a filled rect in pixel coordinates
void Renderer::drawFillRect(const Rect& r, const Colour& c) const
{
	SDL_SetRenderDrawColor(sdl_renderer, c.r, c.g, c.b, c.a);
	SDL_Rect sr;
	sr.h = (int)r.size.h;
	sr.w = (int)r.size.w;
	sr.x = (int)r.pos.x;
	sr.y = (int)r.pos.y;
	SDL_RenderFillRect(sdl_renderer, &sr);
}

//draw a rect in pixel coordinates
void Renderer::drawRect(const Rect& r, const Colour& c) const
{
	SDL_SetRenderDrawColor(sdl_renderer, c.r, c.g, c.b, c.a);
	SDL_Rect sr;
	sr.h = static_cast<int>(r.size.h);
	sr.w = static_cast<int>(r.size.w);
	sr.x = static_cast<int>(r.pos.x);
	sr.y = static_cast<int>(r.pos.y);
	SDL_RenderDrawRect(sdl_renderer, &sr);
}

void Renderer::drawTexture(int textureName, const Rect &r) const
{
	SDL_Rect icon_rect;
	icon_rect.x = static_cast<int>(r.pos.x);
	icon_rect.y = static_cast<int>(r.pos.y);
	icon_rect.w = static_cast<int>(r.size.w);
	icon_rect.h = static_cast<int>(r.size.h);

	SDL_RenderCopy(sdl_renderer, textures[textureName], NULL, &icon_rect);
}

void Renderer::drawTexture(int textureName, const Rect &r, double angle) const
{
	SDL_Rect icon_rect;
	icon_rect.x = static_cast<int>(r.pos.x);
	icon_rect.y = static_cast<int>(r.pos.y);
	icon_rect.w = static_cast<int>(r.size.w);
	icon_rect.h = static_cast<int>(r.size.h);

	SDL_Point centrePoint;
	centrePoint.x = static_cast<int>(r.size.w / 2);
	centrePoint.y = static_cast<int>(r.size.h / 2);

	SDL_RenderCopyEx(sdl_renderer, textures[textureName], NULL, &icon_rect, angle, &centrePoint, SDL_FLIP_NONE);
}

//draw a rect in world coordinates
void Renderer::drawWorldFillRect(const Rect &r, const Colour &c) const
{
	drawFillRect(worldToScreen(r), c);
}

// Draw a rectin world coordinates
void Renderer::drawWorldRect(const Rect &r, 
							 const Colour &c) const
{
	drawRect(worldToScreen(r), c);
}

void Renderer::present() 
{ 
	// Swap buffers
	SDL_RenderPresent(sdl_renderer);
}

void Renderer::clear(const Colour& col) const 
{
	SDL_SetRenderDrawColor(sdl_renderer, col.r, col.g, col.b, col.a);
	SDL_RenderClear(sdl_renderer);

}

Point2D Renderer::worldToScreen(const Point2D &p) const
{
	float x = p.x * windowSize.w / viewportSize.w;
	float y = p.y * windowSize.h / viewportSize.h;
	
	return Point2D(x,y);
}

Rect Renderer::worldToScreen(const Rect &r) const
{
	Point2D p = worldToScreen(r.pos);
	float sw = ceil(r.size.w * (windowSize.w / viewportSize.w));
	float sh = ceil(r.size.h * (windowSize.h / viewportSize.h));
	Rect result = Rect(p, Size2D(sw, sh));
	return result;
}

void Renderer::setViewPort(const Rect &r)
{
	viewportBottomLeft = r.pos;
	viewportSize = r.size;
}

Size2D Renderer::getWindowSize() const
{
	return windowSize;
}

// Destroys SDL_Window and SDL_Renderer
void Renderer::destroy() 
{
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(window);
}

Renderer::~Renderer()
{
	// Deconstructor
}
