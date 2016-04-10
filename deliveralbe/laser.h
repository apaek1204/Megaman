#ifndef LASER_H
#define LASER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include <iostream>
using namespace std;
class laser {

	public:

		static const int LASER_WIDTH = 5;
                static const int LASER_HEIGHT = 5;
		static const float LASER_SPEED = .25;	
		laser( float = 0 , float = 0 , int = 0 );

//		~laser();

		bool collide();
		
		void fired_laser();

		void render(float, float);

		bool loadLaserSprite();
	  
    bool allowChange();
    
    void setX(float);
    
    void setY(float);
    
    void setDir(int);
	  
    void print();
    
    const SDL_Rect getHitBox();
	
    bool check_range();
  private:	
		
		LTexture* gLaserTexture;
		float start_pos;
		float laserX, laserY; 
		int laser_direction;
		float laserX_vel;		
   		bool moving;
    SDL_Rect circleBox;
};

laser::laser( float X_COORD, float Y_COORD, int DIRECTION )
{

gLaserTexture = new LTexture;

laserX = X_COORD;

laserY = Y_COORD;

laserX_vel = 20;

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
if(laserX - start_pos >= range || laserX < 0 ){
  moving = false;
  laserX = -50;
  laserY = -50;
  laser_direction=-1;
}
}

bool laser::check_range(){
cout << laserX << " , " << start_pos << endl;
 if( laserX-start_pos >= 320 || laserX-start_pos <= -320)
	return true;
 else
	return false;
}
void laser::render(float camerax, float cameray)
{
float newlaserX, newlaserY;
newlaserX = laserX - camerax;
newlaserY = laserY - cameray;
gLaserTexture->render( newlaserX, newlaserY );
}

bool laser::loadLaserSprite()
{
bool success = true;

if( !gLaserTexture->loadFromFile("./../assets/sprites/megaman/lasers/3.png"))
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
void laser::setX(float x){
  laserX=x;
  circleBox.x=x;
 if(x > 0) 
	 start_pos=laserX;
 else
	 start_pos = 0;
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
