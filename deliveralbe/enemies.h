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

		virtual void render(float , float, int)=0;

		virtual bool loadSprite()=0;		

		virtual const SDL_Rect getHitBox()=0;
    
    int getX();

    int getY();
	  int getW();
    int getH();
  private:

		bool fire;

		float enemyX, enemyY;
		float enemyX_vel;
		//SDL_Rect circleBox;
};



enemies::enemies(float xCoord, float yCoord){

enemyX = xCoord;

enemyY = yCoord;

fire = false;

enemyX_vel = 0;

//circleBox.x = enemyX;

//circleBox.y = enemyY;

//circleBox.w = 136;

//circleBox.h = 72;

}

/*const SDL_Rect enemies::getHitBox(){
  return circleBox;
}*/

int enemies::getX(){
  return enemyX;
}
int enemies::getY(){
  return enemyY;
}

#endif
