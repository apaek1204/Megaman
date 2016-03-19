#ifndef LASER_H
#define LASER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"

class laser {

	public:

		static const int LASER_WIDTH = 5;
                static const int LASER_HEIGHT = 5;
		static const int LASER_SPEED = 5;	
		laser( int = 0 , int = 0 , int = 0 );

//		~laser();

		bool collide();
		
		void fired_laser();

		void render();

		bool loadLaserSprite();
	  
    bool allowChange();
    
    void setX(int);
    
    void setY(int);
    
    void setDir(int);
	  
    void print();
  private:	
		
		LTexture gLaserTexture;

		int laserX, laserY, laser_direction;
		int laserX_vel;		
    bool moving;
};

laser::laser( int X_COORD, int Y_COORD, int DIRECTION )
{

LTexture gLaserTexture;

laserX = X_COORD;

laserY = Y_COORD;

laserX_vel = 10;

laser_direction = DIRECTION;

moving = false;
}

void laser::fired_laser()
{
moving = true;
if(laser_direction == 1)
	laserX += laserX_vel;
if(laser_direction == 0)
    laserX -= laserX_vel;
if(laserX > 640 || laserX < 0){
  moving = false;
  laserX = -50;
  laserY = -50;
  laser_direction=-1;
}
}

void laser::render()
{
gLaserTexture.render( laserX, laserY );
}

bool laser::loadLaserSprite()
{
bool success = true;

if( !gLaserTexture.loadFromFile("./dot.bmp"))
{
        printf( "Unable to load laser texture! \n");
        success = false;
}
return success;
}

bool laser::allowChange(){
  //printf("%d, %d, %d\n", laserX, laserY, laser_direction);
  return (!moving);
}
void laser::setX(int x){
  laserX=x;
}
void laser::setY(int y){
  laserY=y;
}
void laser::setDir(int d){
  laser_direction = d;
}
void laser::print(){
  printf("%d, %d, %d\n", laserX, laserY, laser_direction);
}
#endif
