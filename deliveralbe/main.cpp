#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "window.h"
#include "megaman.h"
#include "laser.h"

int main( int argc, char* args[] )
{

megaman megaman1;

laser *laser1;

int x , y, DIRECTION;

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
				
				if (megaman1.getfire())
				{
					x = megaman1.getX();
					y = megaman1.getY();
					DIRECTION = megaman1.getdir();
					
				}
				laser1=new laser(x,y,DIRECTION);
				megaman1.move();
				laser1->loadLaserSprite();
				laser1->fired_laser();
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				megaman1.render();
				laser1->render();

				SDL_RenderPresent( gRenderer );
			}
		//}
	}

	close();

	return 0;
}
