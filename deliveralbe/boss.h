#ifndef BOSS_H
#define BOSS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "enemies.h"
#include <vector>
class Boss : public enemies{

        public:

            Boss(float=500, float=400);

			~Boss();

			virtual bool loadSprite();

			virtual void render(float, float, int);

			virtual const SDL_Rect getHitBox();

			virtual void shoot(int);

			virtual void move();
		
			bool inrange( float );

			void subHealth(int);

			int getHealth();

		private:

			vector< LTexture* > gBossTexture;
			float bossX_vel;
			SDL_Rect circleBox;
			float bossY_vel;
			int health;
};

Boss::Boss(float xCoord, float yCoord) : enemies(xCoord, yCoord){
	LTexture* tmp = NULL;
	for( int i = 0; i <6; i++){
		if( i == 0 ){
			tmp = new LTexture(222,174);
			gBossTexture.push_back(tmp);
		}
		if( i == 1 ){
			tmp = new LTexture(222,174);
			gBossTexture.push_back(tmp);

		}
		if( i == 2 ){
			tmp = new LTexture(222,174);
			gBossTexture.push_back(tmp);

		}
		if( i == 3 ){
			tmp = new LTexture(222,174);
			gBossTexture.push_back(tmp);
		}
		if( i == 4 ){
			tmp = new LTexture(222,174);
			gBossTexture.push_back(tmp);
		}
		if(i == 5){
			tmp = new LTexture(222,96);
			gBossTexture.push_back(tmp);
		}
	}

	fire = false;

	enemyX = xCoord;

	enemyY = yCoord;

	bossX_vel = 0;

	bossY_vel = 2;

	circleBox.x = enemyX;

	circleBox.y = enemyY;

	circleBox.w = 222;

	circleBox.h = 174;

	health = 500;
}
Boss::~Boss(){
	for( int i = 0; i < 6; i++ )
		delete gBossTexture[i];
}
void Boss::shoot(int frame){
	if( frame % 120 == 1)
		fire = true;
}

bool Boss::inrange( float x ){
	if( enemyX - x  < 800 )
		return true;
	else
		return false;
}

bool Boss::loadSprite(){
	bool success = true;

	if( !gBossTexture[0]->loadFromFile("./../assets/sprites/enemies/0.png")){
		printf( "Unable to load boss texture! \n");
		success = false;
	}

	if( !gBossTexture[1]->loadFromFile("./../assets/sprites/enemies/1.png")){
		printf( "Unable to load boss texture! \n");
		success = false;
	}

	if( !gBossTexture[2]->loadFromFile("./../assets/sprites/enemies/5.png")){
		printf( "Unable to load boss texture! \n");
		success = false;
	}
	if( !gBossTexture[3]->loadFromFile("./../assets/sprites/enemies/4.png")){
		printf( "Unable to load boss texture! \n");
		success = false;
	}
	if( !gBossTexture[4]->loadFromFile("./../assets/sprites/enemies/6.png")){
		printf( "Unable to load boss texture! \n");
		success = false;
	}

	if( !gBossTexture[5]->loadFromFile("./../assets/sprites/enemies/dead.png")){
		printf( "Unable to load boss texture! \n");
		success = false;
	}

	return success;
}

void Boss::render( float camx, float camy, int frame){
	float newbossX, newbossY;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	newbossX = enemyX - camx;
	newbossY = enemyY - camy;
	if(health > 0)
		gBossTexture[(frame % 20)/4]->render( newbossX, newbossY, NULL, 0.0, NULL,flip);
	else{
		gBossTexture[5]->render( newbossX, newbossY, NULL, 0.0, NULL,flip);
	}
}

const SDL_Rect Boss::getHitBox(){
  return circleBox;
}

void Boss::move(){
	if(health > 0){
		if( enemyY == 150 || enemyY == 300)
				bossY_vel = -bossY_vel;
		circleBox.y+=bossY_vel;
			  }
	else if(enemyY <= 400)
		bossY_vel=1;
	else
		bossY_vel=0;

	enemyY+=bossY_vel;
}
void Boss::subHealth(int a){
  health = health -a;
}
int Boss::getHealth(){
  return health;
}
#endif
