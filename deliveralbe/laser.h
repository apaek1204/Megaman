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
		
	private:	
		
		LTexture gLaserTexture;

		int laserX, laserY, laser_direction;
		int laserX_vel;		
};


laser::laser( int X_COORD, int Y_COORD, int DIRECTION )
{

laserX = X_COORD;

laserY = Y_COORD;

laser_direction = DIRECTION;

}

void laser::fired_laser()
{
if(laser_direction == 0)
	laserX += laserX_vel;
if(laser_direction == 1)
        laserX -= laserX_vel;
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

#endif
