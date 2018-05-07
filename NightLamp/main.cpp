#include "SDL.h"

static const int SCREEN_WIDTH = 160;
static const int SCREEN_HEIGHT = 144;

int main(int argc, char* args[]) 
{ 
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Surface* imageSurface;
	SDL_Renderer* renderer;
	SDL_PixelFormat* pixFormat;
	
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("NightLamp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	screenSurface = SDL_GetWindowSurface(window);

	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;

	imageSurface = SDL_CreateRGBSurface(NULL, 256, 256, 32, rmask, gmask, bmask, amask);

	renderer = SDL_GetRenderer(window);

	pixFormat = imageSurface->format;

	SDL_memset(imageSurface->pixels, SDL_MapRGB(pixFormat, 200, 180, 160), imageSurface->pitch * imageSurface->h);

	Uint32* pxptr = (Uint32*)imageSurface->pixels;
	for (int i = 0; i < 256; i++)
	{		
		for (int j = 0; j < 256; j++)
		{
			Uint32 color = SDL_MapRGB(pixFormat, (i * j)*5 , (i * j)*5, (i * j)*5);
			pxptr[(i*SCREEN_HEIGHT) + j] = color;
		}
	}

	SDL_Event e;

	SDL_Rect srcRect;
	srcRect.h = SCREEN_HEIGHT;
	srcRect.w = SCREEN_WIDTH;
	srcRect.x = 0;
	srcRect.y = 0;

	SDL_Rect dstRect;
	dstRect.h = 0;
	dstRect.w = 0;
	dstRect.x = 0;
	dstRect.y = 0;

	while (true)
	{
		while (SDL_PollEvent(&e) != 0)
		{			
			srcRect.x = (srcRect.x + 1) % 64;
			srcRect.y = (srcRect.y + 1) % 32;
			SDL_BlitSurface(imageSurface, &srcRect, screenSurface, &dstRect);
			SDL_UpdateWindowSurface(window);
			if (e.type == SDL_QUIT)
			{
				break;
			}
		}
	}

	SDL_Quit(); 
	return 0; 
}