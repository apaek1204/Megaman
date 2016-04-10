#ifndef MEGAMAN_H
#define MEGAMAN_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "laser.h"

class megaman{

	public:

		static const int MEGAMAN_WIDTH = 60;
		static const int MEGAMAN_HEIGHT = 60;
		
		static const int MEGAMAN_SPEED = 3;

		megaman(int=0, int=0);

		void handleEvent( SDL_Event& e );
		
		void move();

		void render();

		bool loadSprite();		

		bool getfire();
	
		int getX();

		int getY();

		int getdir();
		
    const SDL_Rect getHitBox();
//		void fire();

	private:

		bool fire;

		LTexture* gMegamanTexture;
		//LTexture gMegamanTexture;

		int megamanX, megamanY, DIRECTION;

		int megamanX_vel, megamanY_vel;

    SDL_Rect circleBox;
};



megaman::megaman(int xCoord, int yCoord){


gMegamanTexture = new LTexture;

megamanX = xCoord;

megamanY = yCoord;

DIRECTION=0;

fire = false;

megamanX_vel = 0;

megamanY_vel = 0;

circleBox.x = megamanX;

circleBox.y = megamanY;

circleBox.w = MEGAMAN_WIDTH;

circleBox.h = MEGAMAN_HEIGHT;
}

bool megaman::loadSprite()
{
bool success = true;

if( !gMegamanTexture->loadFromFile("./../assets/sprites/megaman/movement/0.png"))
{
	printf( "Unable to load megaman texture! \n");
	success = false;
}
return success;
}

void megaman::handleEvent( SDL_Event& e )
{
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
                switch( e.key.keysym.sym )
                {
                        case  SDLK_UP: if (megamanY + MEGAMAN_HEIGHT > 440)
						megamanY_vel = -MEGAMAN_SPEED-10; 
						
						break;
                        case  SDLK_DOWN: megamanY_vel += MEGAMAN_SPEED; break;
                        case  SDLK_LEFT: megamanX_vel -= MEGAMAN_SPEED; DIRECTION = 0; break;
                        case  SDLK_RIGHT: megamanX_vel += MEGAMAN_SPEED; DIRECTION = 1;break;
			//case  SDLK_SPACE: fire = true; break;
                }
        }
        if( e.type == SDL_KEYUP && e.key.repeat == 0 )
        {
                switch( e.key.keysym.sym )
                {
                        case  SDLK_UP: megamanY_vel = 0; break;
                        case  SDLK_DOWN: megamanY_vel -= MEGAMAN_SPEED; break;
                        case  SDLK_LEFT: megamanX_vel += MEGAMAN_SPEED;  break;
                        case  SDLK_RIGHT: megamanX_vel -= MEGAMAN_SPEED;  break;
                	case  SDLK_SPACE: fire = true; break;
		}
        }
}

int megaman::getX()
{
	return(megamanX);
}

int megaman::getY()
{
        return(megamanY);
}

int megaman::getdir()
{
        return(DIRECTION);
}

bool megaman::getfire()
{
        return fire;
}
/*
void megaman::fire()
{
laser laser1(megamanX, megamanY, DIRECTION);
laser1.loadLaserSprite();
}
*/
void megaman::move()
{
  fire=false;
	if(megamanX+megamanX_vel >= 0 && megamanX+megamanX_vel < 640){
    megamanX += megamanX_vel;
    circleBox.x += megamanX_vel;
  }
  if(megamanY+megamanY_vel >= 0 && megamanY+megamanY_vel < 480 - MEGAMAN_HEIGHT)
	  megamanY += megamanY_vel;
	  if (megamanY < 480 - MEGAMAN_HEIGHT){
		megamanY_vel += 1;
    		circleBox.y += megamanY_vel;
		}
}

void megaman::render()
{
        gMegamanTexture->render( megamanX, megamanY );
}

const SDL_Rect megaman::getHitBox(){
  return circleBox;
}

#endif