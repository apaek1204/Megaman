#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "window.h"
#include "megaman.h"
#include "laser.h"
#include "stage.h"
#include "music.h"
#include "mainMenu.h"

int main( int argc, char* args[] ){
	music music0;
	music music1;
	megaman megaman1;
	Stage stage1;
	MainMenu mainmenu1;

	bool start=false;

	int x , y, DIRECTION;
	int frame = 0;
	if( !init() ){
		printf( "Failed to initialize!\n" );
	}
	// main menu
	else{
		if (start == false){
			// load the main menu
			mainmenu1.loadSprite();
			// load music
			music0.Load_music();
			// set quit main menu
			bool quitmm=false;
			// set sdl event variable
			SDL_Event emm;
			
			// loop that displays main menu 
			while ( !quitmm && start == false){
			
				// Play constant music
				if( Mix_PlayingMusic() == 0 ){
					Mix_PlayMusic( music0.mmMusic, -1 );
				}
			
				// check if player quits
				while( SDL_PollEvent( &emm ) != 0 ){
					if( emm.type == SDL_QUIT ){
						quitmm = true;
					}
				}
			
				// check for main menu event
				start=mainmenu1.handle_event(emm);
				
				// render the main menu screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				mainmenu1.Render();
				SDL_RenderPresent( gRenderer );
				SDL_Delay(1000/30);
				
			}
			// close old music
			music0.close_music();
			Mix_HaltMusic();	
		}
		if (start==true){
			// load other
			stage1.loadSprite();
			megaman1.loadSprite();
			music1.Load_music();
			laser laserArray[5];
			for(int i=0; i<5; i++){
				  laserArray[i].setX(-50);
				  laserArray[i].setY(-50);
				  laserArray[i].setDir(-1);
				  laserArray[i].loadLaserSprite();
			}

    
				
			bool quit = false;

			SDL_Event e;
			
			while( !quit ){
				// Play constant music
				if( Mix_PlayingMusic() == 0 ){
					Mix_PlayMusic( music1.mMusic, -1 );
				}
					
				// check if player quits
				while( SDL_PollEvent( &e ) != 0 ){
					if( e.type == SDL_QUIT ){
						quit = true;
					}
	
				megaman1.handleEvent( e );
				}
				
				if (megaman1.getfire()){
					x = megaman1.getX() + 35.0;
					y = megaman1.getY() + 20.0;
					DIRECTION = megaman1.getdir();
       					for(int i=0; i<5; i++){
      						 if(laserArray[i].allowChange()){
             						laserArray[i].setX(x);
              						laserArray[i].setY(y);
              						laserArray[i].setDir(DIRECTION);
              						// Play laser sound effect
              						Mix_PlayChannel( -1, music1.lMusic, 0 );
              						break;
            					}	
          				}         
				}
        
				megaman1.move();
				camera.x = megaman1.getX() + 35 - 320;
				camera.y = 200;//megaman1.getY() + 35 - 300; 
				for(int i=0; i<5; i++){
				  laserArray[i].fired_laser();
	
         	 		}	
       				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				stage1.Render(camera.x, camera.y);
				megaman1.render(camera.x, camera.y, (frame));
				for(int i=0; i<5; i++){
          				laserArray[i].render(camera.x, camera.y);
        			}
				SDL_RenderPresent( gRenderer );
				SDL_Delay(1000/30);

				frame++;
			}
		}

	close();
	music1.close_music();
	}
	return 0;
}


// OUTDATED CODE
// don't know if anyone needs it?

//          SDL_Rect bulletHitBox = laserArray[i].getHitBox();
          //printf("%d, %d, %d, %d\n", enemyHitBox.x, enemyHitBox.y, bulletHitBox.x, bulletHitBox.y);
//          if(SDL_HasIntersection(&enemyHitBox, &bulletHitBox)== SDL_TRUE){
            //printf("hit");
//            laserArray[i].setX(-50);
//            laserArray[i].setY(-50);
//            laserArray[i].setDir(-1);

//if( !megaman1.gMegamanTexture)
		//{
		//	printf( "Failed to load media!\n" );
		//}
		//else
		
/*				if( frame == 27 )
					frame = 0;
				else
					frame++;*/
