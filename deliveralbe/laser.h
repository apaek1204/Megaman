#ifndef LASER_H
#define LASER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class laser {

	public:

		static const int LASER_WIDTH = 5;
                static const int LASER_HEIGHT = 5;
		static const float LASER_SPEED = .25;	
		laser( float = 0 , float = 0 , int = 0, int = 40, int = 40, bool = false);

//		~laser();

		bool collide();
		
		void fired_laser();

		void render(float, float, bool);

		bool loadLaserSprite(int = 0);
		
		bool allowChange();
    
		void setX(float);
    
		void setY(float);

		void setY_vel( float );    
		void setDir(int);
	  
		void print();
    
		const SDL_Rect getHitBox();
	
  private:	
		
		LTexture* gLaserTexture;
		float start_pos;
		float laserX, laserY; 
		int laser_direction;
		float laserX_vel;		
		float laserY_vel;
   		bool moving;
		SDL_Rect circleBox;
		int frame;
};

laser::laser( float X_COORD, float Y_COORD, int DIRECTION, int laserw, int laserh, bool CHARGE )
{

LTexture* tmp = NULL;
frame = 0;
gLaserTexture = new LTexture(laserw, laserh);
laserX = X_COORD;

laserY = Y_COORD;

laserX_vel = 20;
laserY_vel = 0;
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
float range = 420.0;
if(laser_direction == 1){
  circleBox.x += laserX_vel;
        laserX += laserX_vel;
}
if(laser_direction == 0){
  circleBox.x -= laserX_vel;
  laserX -= laserX_vel;
}
circleBox.y += laserY_vel;
laserY += laserY_vel;

if((laserX - start_pos >= range && laser_direction ==1) || (laserX-start_pos <= -range && laser_direction ==0)|| laser_direction==-1){
  //cout << "reset" << endl;
  laserX = -50;
  laserY = -50;
  laser_direction=-1;
  frame = 0;
  moving = false;
}

}

void laser::setY_vel( float newy_vel )
{
	laserY_vel = newy_vel;

}
void laser::render(float camerax, float cameray, bool CHARGE)
{
float newlaserX, newlaserY;
SDL_RendererFlip flip= SDL_FLIP_NONE;
if(laser_direction == 0)
	flip = SDL_FLIP_HORIZONTAL;
newlaserX = laserX - camerax;
newlaserY = laserY - cameray;
gLaserTexture->render( newlaserX, newlaserY, NULL, 0.0,NULL,flip );
	
}

bool laser::loadLaserSprite(int level)
{
bool success = true;
if( level == 0 ){
	if( !gLaserTexture->loadFromFile("./../assets/sprites/megaman/lasers/0.png"))
	{
	        printf( "Unable to load laser texture! \n");
	        success = false;
	}
}
if( level == 1 ){
        if( !gLaserTexture->loadFromFile("./../assets/sprites/megaman/lasers/4.png"))
        {
                printf( "Unable to load laser texture! \n");
                success = false;
        }


}
return success;
}

bool laser::allowChange(){
  //printf("%d, %d, %d\n", laserX, laserY, laser_direction);
  return (!moving);
}
void laser::setX(float x){
  if(x>0)
	start_pos = x;
  else
	start_pos = -500;
  laserX=x;
  circleBox.x=x;
}
void laser::setY(float y){
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
