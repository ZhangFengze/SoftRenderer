#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* argv[] )
{
	if(0!=Catch::Session().run( argc, argv ))
		return 1;

	SDL_Window* gWindow = NULL;
	SDL_Surface* gScreenSurface = NULL;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		return 1;

	SDL_Window* window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if(!window)
		return 1;

	SDL_Surface* surface = SDL_GetWindowSurface( window );

	bool quit = false;
	SDL_Event e;
	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0xFF, 0xFF));
		SDL_UpdateWindowSurface( window );
	}

	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}