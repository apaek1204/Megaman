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
#include <vector>
#include <iterator>
#include "RestartMenu.h"
#include "healthbar.h"
int main( int argc, char* args[] )
{
int m=0;
bool QUIT = false;
bool start = false;
bool restart=false;

RestartMenu restart1;
music music0;
//music music1;
music music1;

healthbar healthbar1;
megaman megaman1;
Stage stage1;
vector< enemies* > AllEnemies;
Boss* Boss1 = new Boss(450, 200);
enemies* tmp = NULL;
unsigned int hittime = 0;
unsigned int deathtimer = 0;
bool DEATHINIT = false;
bool reset = false;

float hitstart = 0;
int death = 0;
int lives = 3;



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
                AllEnemies.push_back(tmp);SDL_Quit();
	//Mix_Quit();
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

int x , y, DIRECTION;

SDL_Rect platforms[4];
platforms[0].x = 0;
platforms[0].y = 470;
platforms[0].w = 1580;SDL_Quit();
	//Mix_Quit();
platforms[0].h = 90;
platforms[1].x = 1700;
platforms[1].y = 410;
platforms[1].w = 910;
platforms[1].h = 90;
platforms[2].x = 2720;
platforms[2].y = 440;SDL_Quit();
	//Mix_Quit();
platforms[2].w = 1930;
platforms[2].h = 90;
platforms[3].x = 4800;
platforms[3].y = 430;
platforms[3].w = 1200;
platforms[3].h = 90;



int frame = 0;
	while (QUIT == false){
		if( !init() )
		{
			QUIT=true;
			printf( "Failed to initialize!\n" );
		}
		else
		{
			RestartMenu restart1;
			music music0;
//music music1;

healthbar healthbar1;
megaman megaman1;
Stage stage1;
vector< enemies* > AllEnemies;
Boss* Boss1 = new Boss(450, 200);
enemies* tmp = NULL;
unsigned int hittime = 0;
unsigned int deathtimer = 0;
bool DEATHINIT = false;
bool reset = false;
bool megahit = false;
float hitstart = 0;
int death = 0;
int lives = 3;


cout << "m is " << m << endl;
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
             
                	if (( start == false) && (restart==false)){
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
                        	                        QUIT=true;
                                        	}
                                	}
                                

                                	start=mainmenu1.handle_event(emm);

                               		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                	SDL_RenderClear( gRenderer );
                                	mainmenu1.Render();
                                	SDL_RenderPresent( gRenderer );
                                	SDL_Delay(1000/30);
				}
				music0.close_music();
                        Mix_HaltMusic();
                        
                     
                
                        }
			
                        
		if ((start == true) && (restart == false)){
			stage1.loadSprite();
			megaman1.loadSprite();
			Boss1->loadSprite();
			healthbar1.loadSprite();
			   music1.Load_music();
			
			Mix_PlayChannel( -1, music1.newlifeMusic, 0 );
			for(int i=0; i < 12; i++)
				AllEnemies[i]->loadSprite();
			laser* laserArray[5];
			laser* ChargedlaserArray[5];
			laser* EnemylaserArray[16];
			laser* Death[6];

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
                	for(int i=0; i<16; i++){
                        	  EnemylaserArray[i] = new laser(-50,-50,-1, 20, 20);
                        	  EnemylaserArray[i]->setX(-50);
                        	  EnemylaserArray[i]->setY(-50);
                        	  EnemylaserArray[i]->setDir(-1);
                        	  EnemylaserArray[i]->loadLaserSprite();
                        }

                	for(int i=0; i<6; i++){
                        	  Death[i] = new laser(-50,-50,-1, 40, 40);
                        	  Death[i]->setX(-50);
                        	  Death[i]->setY(-50);
                        	  Death[i]->setDir(-1);
                        	  Death[i]->loadLaserSprite(2);
                        }
                        
                         SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                         SDL_RenderClear( gRenderer );
                        // stage1.Render(0, 0);
                        // megaman1.
                         SDL_RenderPresent( gRenderer );
                         SDL_Delay(1000/30);
		
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
                                	cout << "in music loop!!" << endl;
                                        Mix_PlayMusic( music1.mMusic, -1 );
                                }

				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
					quit = true;
					QUIT=true;
					}

					bool jumping=megaman1.handleEvent( e );
					
					// jumping sound effect
					if (jumping){
						Mix_PlayChannel( -1, music1.jumpingMusic, 0 );
					}
					
					
					// charging sound effect
					if (  (megaman1.charging==true) ){
						if ( megaman1.total_time == 0 )
							Mix_PlayChannel( -1, music1.chargingMusic, 0);
					}
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
							  Mix_PlayChannel( -1, music1.lMusic, 0 );  
							  megaman1.total_time=0;
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
							Mix_HaltChannel(-1);
							Mix_PlayChannel( -1, music1.clMusic, 0 );
							megaman1.total_time=0;
							megaman1.setchargedfire(false);	
                                                        break;
                                                   }
                                          }
                                }
				for(int j=6; j < 12; j++)
				{
					AllEnemies[j]->shoot(frame);

          				if (AllEnemies[j]->getfire())
          				{
           					 x = AllEnemies[j]->getX() + 35.0;
            					y = AllEnemies[j]->getY() + 20.0;
            					DIRECTION = 0;
            					if(EnemylaserArray[j]->allowChange()){
              						EnemylaserArray[j]->setX(x);
              						EnemylaserArray[j]->setY(y);
              						EnemylaserArray[j]->setDir(DIRECTION);
	      						EnemylaserArray[j]->setY_vel(10);
	      						Mix_PlayChannel(-1, music1.beeshotMusic, 0);
            						  AllEnemies[j]->setfire(false);
    
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
              						AllEnemies[j]->subHealth(1);
            					}
            					if(SDL_HasIntersection(&enemyHitBox, &chargedHitBox)){
              						//charged hit
              						cout << "charged hit"<< endl;
              						cout << i << ", " << j << endl;
              						AllEnemies[j]->subHealth(1);
            					}
           					 if(AllEnemies[j]->getHealth() == 0){
              						AllEnemies[j]->setX(-1000);
              						AllEnemies[j]->setY(-1000);
              						AllEnemies[j]->setXVel(0);
              						AllEnemies[j]->setYVel(0);
            					}
          				}
        			}
        
        			int tempX=megaman1.getX();
        			int tempY=megaman1.getY();
				megaman1.move();
				healthbar1.setX(megaman1.getX()-camera.x+190);
				healthbar1.setY(500+camera.y);
				if (megaman1.getY() > 500)
					megaman1.subtractHealth(10);
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
       	 	//check collision between enemy lasers and megaman/platforms
        	for(int i=0; i<16; i++){
          		SDL_Rect enemyBullet = EnemylaserArray[i]->getHitBox();
          		if(SDL_HasIntersection(&enemyBullet, &megamanHitBox)){
            			megaman1.subtractHealth(1);
            			megaman1.setishit(true); 
            			megaman1.setX_vel(-5);
            			megaman1.setY_vel(-5);
            			hittime = SDL_GetTicks();

            			if(SDL_GetTicks() > megaman1.getInvul() + 1000){
              				megaman1.setInvul(int(SDL_GetTicks()));
              				EnemylaserArray[i]->setX(-50);
              				EnemylaserArray[i]->setY(-50);

            			}
          		}
          		for(int j=0; j<4; j++){
            			if(SDL_HasIntersection(&enemyBullet, &platforms[j])){
              				EnemylaserArray[i]->setX(-50);
              				EnemylaserArray[i]->setY(-50);
            			}
          		}
        	}
        	//check collision between enemies and megaman
        	for(int i=0; i<AllEnemies.size(); i++){
          		SDL_Rect enemyHitBox = AllEnemies[i]->getHitBox();
          		if(SDL_HasIntersection(&megamanHitBox, &enemyHitBox)){
            			if(megaman1.getHealth() >0){
              				megaman1.subtractHealth(1);
//		if( megaman1.getX() + 35 <= AllEnemies[i]->getX()){
					megaman1.setX_vel(-5);
					megaman1.setY_vel(-5);
					hittime = SDL_GetTicks();
					megaman1.setishit(true);
//		}
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
		for(int i = 0; i < 16; i++)
			EnemylaserArray[i]->fired_laser();
				
        
        
        	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		stage1.Render(camera.x, camera.y);
		for(int i = 0; i < 12; i++){
			AllEnemies[i]->move();
			AllEnemies[i]->render(camera.x, camera.y, frame);
		   }
		Boss1->render(camera.x, camera.y, frame);
		if( megaman1.getHealth() > 0)
			megaman1.render(camera.x, camera.y, (frame));
		else{
			if(DEATHINIT == false){
				deathtimer = SDL_GetTicks();
				DEATHINIT = true;
				cout << "death timer start: " << deathtimer << endl;
		  	}
			for ( int i = 0; i < 6; i++){
				if( i == 0 ){
					if(Death[i]->getX() < 0){
							Death[i]->setX(megaman1.getX());
              						Death[i]->setY(megaman1.getY());
              						Death[i]->setDir(0);
              						Death[i]->setY_vel(0);
					}
					Death[i]->fired_laser();
          				Death[i]->render(camera.x, camera.y,false);
				 }
				if( i == 1 ){
					if(Death[i]->getX() < 0){
                                                    Death[i]->setX(megaman1.getX());
                                                    Death[i]->setY(megaman1.getY());
                                                    Death[i]->setDir(0);
                                               	    Death[i]->setY_vel(20);
					}
					Death[i]->fired_laser();
          				Death[i]->render(camera.x, camera.y,false);
				   }
                                                if( i == 2 ){
							if(Death[i]->getX() < 0){
	                                                        Death[i]->setX(megaman1.getX());
	                                                        Death[i]->setY(megaman1.getY());
	                                                        Death[i]->setDir(0);
	                                                        Death[i]->setY_vel(-20);
										}
								Death[i]->fired_laser();
          						Death[i]->render(camera.x, camera.y,false);
                                                            }
                                                if( i == 3 ){
							if(Death[i]->getX() < 0){
                                                        Death[i]->setX(megaman1.getX());
                                                        Death[i]->setY(megaman1.getY());
                                                        Death[i]->setDir(1);
                                                        Death[i]->setY_vel(0);
										}
							Death[i]->fired_laser();
          						Death[i]->render(camera.x, camera.y,false);
                                                            }
                                                if( i == 4 ){
							if(Death[i]->getX() < 0){
	                                                        Death[i]->setX(megaman1.getX());
	                                                        Death[i]->setY(megaman1.getY());
	                                                        Death[i]->setDir(1);
	                                                        Death[i]->setY_vel(20);
										}
								Death[i]->fired_laser();
          						Death[i]->render(camera.x, camera.y,false);
                                                            }
                                                if( i == 5 ){
							if(Death[i]->getX() < 0){
                                                        	Death[i]->setX(megaman1.getX());
                                                        	Death[i]->setY(megaman1.getY());
							        Death[i]->setDir(1);
                                                        	Death[i]->setY_vel(-20);
							}
								Death[i]->fired_laser();
          						Death[i]->render(camera.x, camera.y,false);
                                                            }
						}
			}	
				
				for(int i=0; i<5; i++){
          laserArray[i]->render(camera.x, camera.y,false);
	  ChargedlaserArray[i]->render(camera.x, camera.y,true);
        }
				for( int i = 0; i < 16; i++)
					EnemylaserArray[i]->render(camera.x, camera.y, false);
				healthbar1.render(megaman1.getX()-camera.x-50, 300, megaman1.getHealth()-1);
				SDL_RenderPresent( gRenderer );
				SDL_Delay(1000/30);
				if( SDL_GetTicks() - hittime >= 350 && megaman1.getishit()){
					megaman1.setX_vel(0);
					megaman1.setY_vel(0);
					megaman1.setishit(false);
					}

/*				if( frame == 27 )
					frame = 0;
				else
					frame++;*/
				frame++;
				if( frame == 100 )
					frame = 0;
				if( megaman1.getHealth() <= 0 )
					cout << SDL_GetTicks() - deathtimer << endl;
				if( SDL_GetTicks() - deathtimer >= 1000 && megaman1.getHealth() <= 0 ){
					if( lives > 0 ){
						megaman1.setHealth(10);
						megaman1.setX( 250 );
						megaman1.setY( 0 );
						DEATHINIT = false;
						lives -=1;
								      }
					if( lives == 0 ){
						restart = true;
						quit=true;				 
				 	}
			}
		//}
		
		if ((start == true ) && (restart == true)){
			restart1.loadSprite();
                        
                        bool quitrm=false;
                        SDL_Event erm;
                        erm.type=0;

                        while ( !quitrm && restart == true){
				erm.type=0;
                                //if( Mix_PlayingMusic() == 0 ){
                                //        Mix_PlayMusic( music0.mmMusic, -1 );
                                //}

                                while( SDL_PollEvent( &erm ) != 0 ){
                                        if( erm.type == SDL_QUIT ){
                                                quitrm = true;
                                                QUIT=true;
                                        }
                                }

                                restart=restart1.handle_event(erm);

                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear( gRenderer );
                                restart1.Render();
                                SDL_RenderPresent( gRenderer );
                                SDL_Delay(1000/30);
                                
                               if (restart == false){
                               	//Mix_PlayingMusic()=0;
                               	//music1.close_music();
                              	//delete music1;
                               	close();}
                                
                             

		
		}
		
	}
	}
	}
	}
	}

	}close();
	//Mix_Quit();
	//music1[m]->close_music();
	music1.close_music();
	SDL_Quit();
	Mix_Quit();
	return 0;
}
