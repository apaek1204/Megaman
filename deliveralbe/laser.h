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
    
    const SDL_Rect getHitBox();
  private:	
		
		LTexture gLaserTexture;

		int laserX, laserY, laser_direction;
		int laserX_vel;		
    bool moving;
    SDL_Rect circleBox;
};

laser::laser( int X_COORD, int Y_COORD, int DIRECTION )
{

LTexture gLaserTexture;

laserX = X_COORD;

laserY = Y_COORD;

laserX_vel = 5;

laser_direction = DIRECTION;

moving = false;

circleBox.x = laserX; 
circleBox.y = laserY;
circleBox.w = LASER_WIDTH;
circleBox.h = LASER_HEIGHT;
}

void laser::fired_laser()
{
moving = true;
if(laser_direction == 1){
  circleBox.x += laserX_vel;
	laserX += laserX_vel;
}
if(laser_direction == 0){
  circleBox.x -= laserX_vel;
  laserX -= laserX_vel;
}
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
  circleBox.x=x;
}
void laser::setY(int y){
  laserY=y;
  circleBox.y=y;
}
void laser::setDir(int d){
  laser_direction = d;
}
void laser::print(){
  printf("%d, %d, %d\n", laserX, laserY, laser_direction);
}
const SDL_Rect laser::getHitBox(){
  return(circleBox);
}
#endif
