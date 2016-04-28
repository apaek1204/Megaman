#ifndef TURRET_H
#define TURRET_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "enemies.h"
#include <vector>
class Turret : public enemies{

        public:

			Turret(float=500, float=400, int = 1);

			virtual bool loadSprite();

			virtual void render(float, float, int);
	
			virtual void shoot(int);

			const SDL_Rect getHitBox();

			virtual void move();
			virtual void setX(int);
			virtual void setY(int);
			virtual void setXVel(int);
			virtual void setYVel(int);
        private:

			vector< LTexture* > gEnemyTexture;
			int platform;
			float enemyX, enemyY;
			float enemyX_vel, enemyY_vel;
			SDL_Rect circleBox;
			float startX;
			SDL_RendererFlip flip;
};

Turret::Turret(float xCoord, float yCoord, int plat) : enemies(xCoord, yCoord){
	LTexture* tmp = NULL;
	for( int i = 0; i <9; i++){
		if( i == 0 ){
				tmp = new LTexture(136,72);
				gEnemyTexture.push_back(tmp);
		}
		if( i == 1 ){
				tmp = new LTexture(156,72);
				gEnemyTexture.push_back(tmp);

		}
	}
	enemyX = xCoord;
	startX = xCoord;
	enemyY = yCoord;
	enemyX_vel = 6;

	flip = SDL_FLIP_HORIZONTAL;

	platform = plat;

	circleBox.x = enemyX;

	circleBox.y = enemyY + 30;

	circleBox.w = 135;

	circleBox.h = 74;
}

bool Turret::loadSprite(){
	bool success = true;

	if( !gEnemyTexture[0]->loadFromFile("./../assets/sprites/enemies/17.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}
	if( !gEnemyTexture[1]->loadFromFile("./../assets/sprites/enemies/18.png")){
		printf( "Unable to load enemy texture! \n");
		success = false;
	}

	return success;
}
void Turret::shoot(int a){
 //turret does not shoot	
}
const SDL_Rect Turret::getHitBox(){
	return circleBox;
}
void Turret::render( float camx, float camy, int frame){
	float newenemyX, newenemyY;
	newenemyX = enemyX - camx;
	newenemyY = enemyY - camy;
	gEnemyTexture[(frame % 8)/4]->render( newenemyX, newenemyY, NULL, 0.0, NULL,flip);
}

void Turret::move(){
	if(enemyX >= startX +400 || enemyX <= startX - 400){
		enemyX_vel = -enemyX_vel;
		if(startX < enemyX)
			flip = SDL_FLIP_NONE;
		else
			flip = SDL_FLIP_HORIZONTAL;
	}		
	enemyX+= enemyX_vel;
	circleBox.x+= enemyX_vel;
}
void Turret::setX(int a){
	circleBox.x = a;
	enemyX = a;
}

void Turret::setY(int a){
	enemyY = a;
	circleBox.y = a;
}
void Turret::setXVel(int a){
	enemyX_vel = a;
}
void Turret:: setYVel(int a){
	enemyY_vel = a;
}
#endif
