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

laser laserArray[5];
for(int i=0; i<5; i++){
  laserArray[i].setX(-50);
  laserArray[i].setY(-50);
  laserArray[i].setDir(-1);
}
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
          for(int i=0; i<5; i++){
            printf("%d, ", i);
            laserArray[i].print();

            if(laserArray[i].allowChange()){
              laserArray[i].setX(x);
              laserArray[i].setY(y);
              laserArray[i].setDir(DIRECTION);
              break;
            }
          }         
				}

				megaman1.move();
				for(int i=0; i<5; i++){
          laserArray[i].loadLaserSprite();
				  laserArray[i].fired_laser();
        }
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				megaman1.render();
				for(int i=0; i<5; i++){
          laserArray[i].render();
        }
				SDL_RenderPresent( gRenderer );
			}
		//}
	}

	close();

	return 0;
}
