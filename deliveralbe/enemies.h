#ifndef ENEMIES_H
#define ENEMIES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "laser.h"
#include <vector>
class enemies{

	public:

		enemies(float=500, float=400);

		void render(float , float, int);

		bool loadSprite();		

		const SDL_Rect getHitBox();

	private:

		bool fire;

		vector< LTexture* > gEnemyTexture;

		float enemyX, enemyY;
		float enemyX_vel, enemyY_vel;
		SDL_Rect circleBox;
};



enemies::enemies(float xCoord, float yCoord){

LTexture* tmp = NULL;

for( int i = 0; i < 2; i++){
	if(i == 0)
		tmp = new LTexture(136,72);
	if(i == 1)
		tmp = new LTexture(156,72);
	gEnemyTexture.push_back(tmp);
}
enemyX = xCoord;

enemyY = yCoord;

fire = false;

enemyX_vel = 0;

enemyY_vel = 0;

circleBox.x = enemyX;

circleBox.y = enemyY;

circleBox.w = 136;

circleBox.h = 72;

}

bool enemies::loadSprite()
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

void enemies::render( float camx, float camy, int frame)
{
float newenemyX, newenemyY;
SDL_RendererFlip flip = SDL_FLIP_NONE;
newenemyX = enemyX - camx;
newenemyY = enemyY - camy;
gEnemyTexture[(frame % 8)/4]->render( newenemyX, newenemyY, NULL, 0.0, NULL,flip);
}

const SDL_Rect enemies::getHitBox(){
  return circleBox;
}

#endif
