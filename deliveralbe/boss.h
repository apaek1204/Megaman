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

                virtual bool loadSprite();

                virtual void render(float, float, int);

		virtual const SDL_Rect getHitBox();

		virtual void shoot(int);

		virtual void move();
	
		bool inrange( float );
        private:

                vector< LTexture* > gBossTexture;

                float bossX, bossY;
                float bossX_vel;
                SDL_Rect circleBox;
		float bossY_vel;
};

Boss::Boss(float xCoord, float yCoord) : enemies(xCoord, yCoord)
{
LTexture* tmp = NULL;
for( int i = 0; i <9; i++){
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
}

fire = false;

bossX = xCoord;

bossY = yCoord;

bossX_vel = 0;

bossY_vel = 0;

circleBox.x = bossX;

circleBox.y = bossY;

circleBox.w = 72;

circleBox.h = 72;
}

void Boss::shoot(int frame)
{
	if( frame % 120 == 1)
		fire = true;
}

bool Boss::inrange( float x )
{
	if( bossX - x  < 800 )
		return true;
	else
		return false;
}

bool Boss::loadSprite()
{
bool success = true;

if( !gBossTexture[0]->loadFromFile("./../assets/sprites/enemies/0.png"))
{
        printf( "Unable to load boss texture! \n");
        success = false;
}

if( !gBossTexture[1]->loadFromFile("./../assets/sprites/enemies/1.png"))
{
        printf( "Unable to load boss texture! \n");
        success = false;
}

if( !gBossTexture[2]->loadFromFile("./../assets/sprites/enemies/5.png"))
{
        printf( "Unable to load boss texture! \n");
        success = false;
}
if( !gBossTexture[3]->loadFromFile("./../assets/sprites/enemies/4.png"))
{
        printf( "Unable to load boss texture! \n");
        success = false;
}
if( !gBossTexture[4]->loadFromFile("./../assets/sprites/enemies/6.png"))
{
        printf( "Unable to load boss texture! \n");
        success = false;
}

return success;
}

void Boss::render( float camx, float camy, int frame)
{
float newbossX, newbossY;
SDL_RendererFlip flip = SDL_FLIP_NONE;
newbossX = bossX - camx;
newbossY = bossY - camy;
gBossTexture[(frame % 20)/4]->render( newbossX, newbossY, NULL, 0.0, NULL,flip);
}

const SDL_Rect Boss::getHitBox(){
  return circleBox;
}

void Boss::move()
{
if( bossY <= 300 )
	bossY+=bossY_vel;
else
	bossY-=bossY_vel;
}
#endif
