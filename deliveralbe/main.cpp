#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "window.h"
#include "megaman.h"
#include "laser.h"
#include "stage.h"
#include <SDL2/SDL_mixer.h>
#include "music.h"
#include "enemies.h"
#include "mainMenu.h"
#include "bee.h"
#include "turret.h"
#include "boss.h"

int main( int argc, char* args[] )
{
music music0;
music music1;
megaman megaman1;
Stage stage1;
vector< enemies* > AllEnemies;
Boss* Boss1 = new Boss(450, 200);
enemies* tmp = NULL;
for(int i = 0; i < 12; i++){
	if( i == 0){
		tmp = new Turret(900,390);
		AllEnemies.push_back(tmp);
		   }
        if( i == 1){
                tmp = new Turret(200,390);
                cout << tmp->getX() << ", " << tmp->getY()<< endl;
                AllEnemies.push_back(tmp);
                   }

        if( i == 2){
                tmp = new Turret(1300,390);
                AllEnemies.push_back(tmp);
                   }
        if( i == 3){
                tmp = new Turret(1550,400);
                AllEnemies.push_back(tmp);
                   }
        if( i == 4){
                tmp = new Turret(5050,430);
                AllEnemies.push_back(tmp);
                   }
        if( i == 5){
                tmp = new Turret(5400,430);
                AllEnemies.push_back(tmp);
                   }
       if( i == 6){
                tmp = new Bee(450,250);
                AllEnemies.push_back(tmp);
                   }
        if( i == 7){
                tmp = new Bee(800,250);
                AllEnemies.push_back(tmp);
                   }

        if( i == 8){
                tmp = new Bee(1100,200);
                AllEnemies.push_back(tmp);
                   }
        if( i == 9){
                tmp = new Bee(1800,200);
                AllEnemies.push_back(tmp);
                   }
        if( i == 10){
                tmp = new Bee(3050,250);
                AllEnemies.push_back(tmp);
                   }
        if( i == 11){
                tmp = new Bee(3500,250);
                AllEnemies.push_back(tmp);
                   }

}
MainMenu mainmenu1;
bool start = false;
int x , y, DIRECTION;

SDL_Rect platforms[4];
platforms[0].x = 0;
platforms[0].y = 470;
platforms[0].w = 1580;
platforms[0].h = 90;
platforms[1].x = 1700;
platforms[1].y = 410;
platforms[1].w = 910;
platforms[1].h = 90;
platforms[2].x = 2720;
platforms[2].y = 440;
platforms[2].w = 1930;
platforms[2].h = 90;
platforms[3].x = 4800;
platforms[3].y = 430;
platforms[3].w = 1200;
platforms[3].h = 90;



int frame = 0;
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
                if (start == false){
                        mainmenu1.loadSprite();
                        music0.Load_music();
                        bool quitmm=false;
                        SDL_Event emm;

                        while ( !quitmm && start == false){

                                if( Mix_PlayingMusic() == 0 ){
                                        Mix_PlayMusic( music0.mmMusic, -1 );
                                }

                                while( SDL_PollEvent( &emm ) != 0 ){
                                        if( emm.type == SDL_QUIT ){
                                                quitmm = true;
                                        }
                                }

                                start=mainmenu1.handle_event(emm);

                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear( gRenderer );
                                mainmenu1.Render();
                                SDL_RenderPresent( gRenderer );
                                SDL_Delay(1000/30);

                        }
			}
                        music0.close_music();
                        Mix_HaltMusic();
                }
		if (start == true){
			stage1.loadSprite();
			megaman1.loadSprite();
			Boss1->loadSprite();
			music1.Load_music();
			for(int i=0; i < 12; i++)
				AllEnemies[i]->loadSprite();
			laser* laserArray[5];
			laser* ChargedlaserArray[5];
		for(int i=0; i<5; i++){
			  laserArray[i] = new laser(-50,-50,-1,20,20);
			  laserArray[i]->setX(-50);
			  laserArray[i]->setY(-50);
			  laserArray[i]->setDir(-1);
			  laserArray[i]->loadLaserSprite();
			}
                for(int i=0; i<5; i++){
			  ChargedlaserArray[i] = new laser(-50,-50,-1, 40, 40);
                          ChargedlaserArray[i]->setX(-50);
                          ChargedlaserArray[i]->setY(-50);
                          ChargedlaserArray[i]->setDir(-1);
                          ChargedlaserArray[i]->loadLaserSprite(1);
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
                                if( Mix_PlayingMusic() == 0 ){
                                        Mix_PlayMusic( music1.mMusic, -1 );
                                }

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
           					 
                     if(laserArray[i]->allowChange()){
              						laserArray[i]->setX(x);
              						laserArray[i]->setY(y);
              						laserArray[i]->setDir(DIRECTION);
							            cout << "NORMAL SHOT" << endl;      
                          SDL_Rect laserHitBox = laserArray[i]->getHitBox();
                          cout << laserHitBox.x << ", " << laserHitBox.y<< endl;
              						break;
	      									}	
          						}         
				}
                                if (megaman1.getchargedfire())
                                {
                                        x = megaman1.getX() + 35.0;
                                        y = megaman1.getY() + 20.0;
                                        DIRECTION = megaman1.getdir();
                                        for(int i=0; i<5; i++){
                                                 if(ChargedlaserArray[i]->allowChange()){
                                                        ChargedlaserArray[i]->setX(x);
                                                        ChargedlaserArray[i]->setY(y);
                                                        ChargedlaserArray[i]->setDir(DIRECTION);
							cout << "CHARGED SHOT" << endl;
							megaman1.setchargedfire(false);	
                                                        break;
                                                                                }
                                                        }
                                }
        //check for collision between enemies and laser
        for(int i=0; i<5; i++){
          for(int j=0; j<AllEnemies.size(); j++){
            SDL_Rect enemyHitBox = AllEnemies[j]->getHitBox();
            SDL_Rect laserHitBox = laserArray[i]->getHitBox();
            SDL_Rect chargedHitBox = ChargedlaserArray[i]->getHitBox();
            if(SDL_HasIntersection(&enemyHitBox, &laserHitBox)){
              //normal laser hit
              laserArray[i]->setX(-50);
              laserArray[i]->setY(-50);
            }
            if(SDL_HasIntersection(&enemyHitBox, &chargedHitBox)){
              //charged hit
              cout << "charged hit"<< endl;
            }
          }
        }
        
        int tempX=megaman1.getX();
        int tempY=megaman1.getY();
				megaman1.move();
        //cout << tempX << ":" << tempY << endl;
        SDL_Rect megamanHitBox = megaman1.getHitBox();
          for(int i=0; i<4; i++){
          if(SDL_HasIntersection(&megamanHitBox, &platforms[i])){
            if(tempY+70 <= platforms[i].y){
              megaman1.setY(platforms[i].y - 70);
            }
            else if(tempX < platforms[i].x){
              megaman1.setX(tempX);
              megaman1.setY(tempY);
              cout << "from left" << endl;
	            megaman1.setonwall(1);
            }
            else{
              megaman1.setonwall(0);
              megaman1.setX(tempX);
              megaman1.setY(tempY);
              cout << "from right" << endl;
            }
          }
        }
        //check collision between enemies and megaman
        for(int i=0; i<AllEnemies.size(); i++){
          SDL_Rect enemyHitBox = AllEnemies[i]->getHitBox();
          if(SDL_HasIntersection(&megamanHitBox, &enemyHitBox)){
            if(megaman1.getHealth() >0){
              megaman1.subtractHealth(1);
              if(SDL_GetTicks() > megaman1.getInvul() + 1000){
                megaman1.setInvul(int(SDL_GetTicks()));
              }
            }
            else{
              cout << "dead" << endl;
            }
          }
        }
				camera.x = megaman1.getX() + 35 - 320;
				camera.y = 200;//megaman1.getY() + 35 - 300; 
				for(int i=0; i<5; i++){
				  laserArray[i]->fired_laser();
				  ChargedlaserArray[i]->fired_laser();
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
				stage1.Render(camera.x, camera.y);
				for(int i = 0; i < 12; i++)
					AllEnemies[i]->render(camera.x, camera.y, frame);
				Boss1->render(camera.x, camera.y, frame);
				megaman1.render(camera.x, camera.y, (frame));
				for(int i=0; i<5; i++){
          laserArray[i]->render(camera.x, camera.y,false);
	  ChargedlaserArray[i]->render(camera.x, camera.y,true);
        }
				SDL_RenderPresent( gRenderer );
				SDL_Delay(1000/30);
/*				if( frame == 27 )
					frame = 0;
				else
					frame++;*/
				frame++;
			}
		//}
	}

	close();
	music1.close_music();
}

	return 0;
}
