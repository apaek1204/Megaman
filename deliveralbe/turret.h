#ifndef TURRET_H
#define TURRET_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "enemies.h"
#include <vector>
class Turret : public enemies{

        public:

                Turret(float=500, float=400);

                virtual bool loadSprite();

                virtual void render(float, float, int);

                const SDL_Rect getHitBox();

        private:

                vector< LTexture* > gEnemyTexture;

                float enemyX, enemyY;
                float enemyX_vel, enemyY_vel;
                SDL_Rect circleBox;
};

Turret::Turret(float xCoord, float yCoord) : enemies(xCoord, yCoord)
{
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
enemyY = yCoord;
enemyX_vel = 0;

circleBox.x = enemyX;

circleBox.y = enemyY;

circleBox.w = 72;

circleBox.h = 72;
}

bool Turret::loadSprite()
{
bool success = true;

if( !gEnemyTexture[0]->loadFromFile("./../assets/sprites/enemies/17.png"))
{
        printf( "Unable to load enemy texture! \n");
        success = false;
}
if( !gEnemyTexture[1]->loadFromFile("./../assets/sprites/enemies/18.png"))
{
        printf( "Unable to load enemy texture! \n");
        success = false;
}

return success;
}

void Turret::render( float camx, float camy, int frame)
{
float newenemyX, newenemyY;
SDL_RendererFlip flip = SDL_FLIP_NONE;
newenemyX = enemyX - camx;
newenemyY = enemyY - camy;
gEnemyTexture[(frame % 8)/4]->render( newenemyX, newenemyY, NULL, 0.0, NULL,flip);
}
#endif
