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

int x , y, DIRECTION;

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
	megaman1.loadSprite();
	laser laserArray[5];
		for(int i=0; i<5; i++){
			  laserArray[i].setX(-50);
			  laserArray[i].setY(-50);
			  laserArray[i].setDir(-1);
			  laserArray[i].loadLaserSprite();
			}

    //if( !megaman1.gMegamanTexture)
		//{
		//	printf( "Failed to load media!\n" );
		//}
		//else
		{	
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
					x = megaman1.getX() + 35.0;
					y = megaman1.getY() + 20.0;
					DIRECTION = megaman1.getdir();
          				for(int i=0; i<5; i++){
           					 if(laserArray[i].allowChange()){
              						laserArray[i].setX(x);
              						laserArray[i].setY(y);
              						laserArray[i].setDir(DIRECTION);
              						break;
            									}	
          						}         
				}
        
				megaman1.move();
				camera.x = megaman1.getX() + 35 - 320;
				camera.y = 100;//megaman1.getY() + 35 - 300; 
				for(int i=0; i<5; i++){
				  laserArray[i].fired_laser();
//          SDL_Rect bulletHitBox = laserArray[i].getHitBox();
          //printf("%d, %d, %d, %d\n", enemyHitBox.x, enemyHitBox.y, bulletHitBox.x, bulletHitBox.y);
//          if(SDL_HasIntersection(&enemyHitBox, &bulletHitBox)== SDL_TRUE){
            //printf("hit");
//            laserArray[i].setX(-50);
//            laserArray[i].setY(-50);
//            laserArray[i].setDir(-1);
          }
//        }
				
        
        
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				megaman1.render(camera.x, camera.y);
				for(int i=0; i<5; i++){
          laserArray[i].render(camera.x, camera.y);
        }
				SDL_RenderPresent( gRenderer );
				SDL_Delay(1000/30);
			}
		//}
	}

	close();
}
	return 0;
}
