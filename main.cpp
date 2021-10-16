#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <SDL.h>
#include <stdio.h>
#include "Math.h"
#include "RenderTarget.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void BlitRenderTarget(const render::RenderTarget& source, SDL_Surface* dest)
{
	SDL_Surface* image = SDL_CreateRGBSurfaceWithFormat(0, source.width, source.height, 24, SDL_PIXELFORMAT_RGB24);
	if (!image)
		return;

	SDL_LockSurface(image);
	for (size_t x = 0;x < source.width;++x)
	{
		for (size_t y = 0;y < source.height;++y)
		{
			auto color = source.rgb(x, y);
			size_t index = (x + y * source.width) * 3;
			((uint8_t*)image->pixels)[index] = render::Clamp((int)color.r * 255, 0, 255);
			((uint8_t*)image->pixels)[index + 1] = render::Clamp((int)color.g * 255, 0, 255);
			((uint8_t*)image->pixels)[index + 2] = render::Clamp((int)color.b * 255, 0, 255);
		}
	}
	SDL_UnlockSurface(image);

	SDL_BlitScaled(image, NULL, dest, NULL);
	SDL_FreeSurface(image);
}

int main(int argc, char* argv[])
{
	if (0 != Catch::Session().run(argc, argv))
		return 1;

	SDL_Window* gWindow = NULL;
	SDL_Surface* gScreenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;

	SDL_Window* window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
		return 1;

	SDL_Surface* surface = SDL_GetWindowSurface(window);

	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		auto r = render::RenderTarget::Create(surface->w, surface->h, { 1,1,1 });
		BlitRenderTarget(r, surface);
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}