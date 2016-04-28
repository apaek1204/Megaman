#ifndef BEE_H
#define BEE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "enemies.h"
#include <vector>
class Bee : public enemies{

        public:

            Bee(float=500, float=400);

			~Bee();

			virtual bool loadSprite();
	
			virtual void render(float, float, int);

			const SDL_Rect getHitBox();
		
			virtual void move();

	        virtual void shoot(int);
		
			virtual void setX(int);
                
			virtual void setY(int);

			virtual void setXVel(int);
			
			virtual void setYVel(int);

          private:
                vector< LTexture* > gEnemyTexture;
                float enemyX_vel, enemyY_vel;
                SDL_Rect circleBox;
				float startX;
};

Bee::Bee(float xCoord, float yCoord) : enemies( xCoord, yCoord ){
	//constructor from enemies
	LTexture* tmp = NULL;
	for( int i = 0; i <9; i++){
		if( i == 0 ){
			tmp = new LTexture(70,72);
			gEnemyTexture.push_back(tmp);
		}
		if( i == 1 ){
			tmp = new LTexture(72,76);
			gEnemyTexture.push_back(tmp);

		}
		if( i == 2 ){
			tmp = new LTexture(50,80);
			gEnemyTexture.push_back(tmp);

		}
		if( i == 3 ){
			tmp = new LTexture(70,74);
			gEnemyTexture.push_back(tmp);
		}
		if( i == 4 ){
			tmp = new LTexture(72,78);
			gEnemyTexture.push_back(tmp);
		}
		if( i == 5 ){
			tmp = new LTexture(50,82);
			gEnemyTexture.push_back(tmp);
		}
		if( i == 6 ){
			tmp = new LTexture(66,78);
			gEnemyTexture.push_back(tmp);
		}
		if( i == 7 ){
			tmp = new LTexture(72,80);
			gEnemyTexture.push_back(tmp);
		}
		if( i == 8 ){
			tmp = new LTexture(50,84);
			gEnemyTexture.push_back(tmp);
		}
	}
	health = 4;
	enemyX = xCoord;

	enemyY = yCoord;

	enemyX_vel = 2;

	enemyY_vel = 1;

	startX = enemyX;

	circleBox.x = enemyX;

	circleBox.y = enemyY;

	circleBox.w = 72;

	circleBox.h = 72;
}

Bee::~Bee(){
	for( int i = 0; i < 9; i++)
		delete gEnemyTexture[i];
}
void Bee::shoot( int frame ){
	if( frame % 60 == 2 )
		fire = true;
}	
void Bee::move(){
	if( enemyX == startX + 100){
		enemyX_vel=-enemyX_vel;
	}
	if( enemyX == startX - 100){
		enemyX_vel=-enemyX_vel;
	}
	enemyX += enemyX_vel;
	circleBox.x+= enemyX_vel;
	if ( enemyY == 300 ){
		enemyY_vel=-enemyY_vel;
	}
	if (enemyY == 150 ){
		enemyY_vel=-enemyY_vel;
	}
	enemyY+= enemyY_vel;
	circleBox.y+= enemyY_vel;
}	
bool Bee::loadSprite(){

	bool success = true;

	if( !gEnemyTexture[0]->loadFromFile("./../assets/sprites/enemies/8.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}

	if( !gEnemyTexture[1]->loadFromFile("./../assets/sprites/enemies/9.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}

	if( !gEnemyTexture[2]->loadFromFile("./../assets/sprites/enemies/10.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}
	if( !gEnemyTexture[3]->loadFromFile("./../assets/sprites/enemies/11.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}
	if( !gEnemyTexture[4]->loadFromFile("./../assets/sprites/enemies/12.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}
	if( !gEnemyTexture[5]->loadFromFile("./../assets/sprites/enemies/13.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}
	if( !gEnemyTexture[6]->loadFromFile("./../assets/sprites/enemies/14.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}
	if( !gEnemyTexture[7]->loadFromFile("./../assets/sprites/enemies/15.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}
	if( !gEnemyTexture[8]->loadFromFile("./../assets/sprites/enemies/16.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}

	return success;
}
const SDL_Rect Bee::getHitBox(){
  return circleBox;
}
void Bee::render( float camx, float camy, int frame)
{
	float newenemyX, newenemyY;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	newenemyX = enemyX - camx;
	newenemyY = enemyY - camy;
	gEnemyTexture[(frame % 32)/4]->render( newenemyX, newenemyY, NULL, 0.0, NULL,flip);
}

void Bee::setX(int a){
  enemyX = a;
  circleBox.x = a;
}
void Bee::setY(int a){
  enemyY = a;
  circleBox.y = a;
}
void Bee::setXVel(int a){
  enemyX_vel = a;
}
void Bee::setYVel(int a){
  enemyY_vel = a;
}
#endif
