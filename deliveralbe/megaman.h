#ifndef MEGAMAN_H
#define MEGAMAN_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "laser.h"

class megaman{

	public:

		static const int MEGAMAN_WIDTH = 70;
		static const int MEGAMAN_HEIGHT = 70;
		
		static const float MEGAMAN_SPEED = 5;

		megaman(float=0, float=0);

		void handleEvent( SDL_Event& e );
		
		void move();

		void render(float , float);

		bool loadSprite();		

		bool getfire();
	
		float getX();

		float getY();

		int getdir();
		
    const SDL_Rect getHitBox();
//		void fire();

	private:

		bool fire;

		LTexture* gMegamanTexture;
		//LTexture gMegamanTexture;

		float megamanX, megamanY;
		int  DIRECTION;

		float megamanX_vel, megamanY_vel;

    SDL_Rect circleBox;
};



megaman::megaman(float xCoord, float yCoord){


gMegamanTexture = new LTexture(70,70);

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
                        case  SDLK_UP: if (megamanY + MEGAMAN_HEIGHT > 400.0 && megamanY+ MEGAMAN_HEIGHT >= 460)
						megamanY_vel = -MEGAMAN_SPEED-7.0; 
						
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

float megaman::getX()
{
	return(megamanX);
}

float megaman::getY()
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
		megamanY_vel +=.75; 
    		circleBox.y += megamanY_vel;
		}
}

void megaman::render( float camx, float camy)
{
float newmegamanX, newmegamanY;
newmegamanX = megamanX - camx;
newmegamanY = megamanY - camy;
        gMegamanTexture->render( newmegamanX, newmegamanY );
}

const SDL_Rect megaman::getHitBox(){
  return circleBox;
}

#endif
