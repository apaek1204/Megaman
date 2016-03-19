#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "window.h"
#include "megaman.h"

int main( int argc, char* args[] )
{

megaman megaman1;

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
	megaman1.loadSprite();
		//if( !megaman1.gMegamanTexture)
		//{
		//	printf( "Failed to load media!\n" );
		//}
		//else
		//{	
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

					megaman1.handleEvent( e );
				}

				megaman1.move();

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				megaman1.render();

				SDL_RenderPresent( gRenderer );
			}
		//}
	}

	close();

	return 0;
}
