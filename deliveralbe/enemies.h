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
    
		virtual void move()=0;
		
		int getX();

		int getY();

		int getHealth();

    void subHealth(int);
    
    virtual void setX(int);

    virtual void setY(int);
    virtual void setXVel(int);
    virtual void setYVel(int);
 protected:
		bool fire;
		float enemyX, enemyY;
		float enemyX_vel, enemyY_vel;
    int health;
};



enemies::enemies(float xCoord, float yCoord){

enemyX = xCoord;

enemyY = yCoord;

fire = false;

enemyX_vel = 0;

enemyY_vel = 0;

health = 10;
}

int enemies::getX(){
  return enemyX;
}
int enemies::getY(){
  return enemyY;
}

int enemies::getHealth(){
  return health;
}

void enemies::subHealth(int a){
  health = health - a;
}
void enemies::setX(int a){
  enemyX = a;
}
void enemies::setY(int a){
  enemyY = a;
}
void enemies::setXVel(int a){
  enemyX_vel = a;
}
void enemies::setYVel(int a){
  enemyY_vel = a;
}

#endif
