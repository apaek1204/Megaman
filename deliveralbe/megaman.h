#ifndef MEGAMAN_H
#define MEGAMAN_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
class megaman{

	public:

		static const int MEGAMAN_WIDTH = 20;
		static const int MEGAMAN_HEIGHT = 20;
		
		static const int MEGAMAN_SPEED = 10;

		megaman();

		void handleEvent( SDL_Event& e );
		
		void move();

		void render();

		bool loadSprite();		
		
		void fire();

	private:

		LTexture gMegamanTexture;

		int megamanX, megamanY;

		int megamanX_vel, megamanY_vel;
};

#endif

LTexture gMegamanTexture;

megaman::megaman(){

megamanX = 0;

megamanY = 0;

megamanX_vel = 0;

megamanY_vel = 0;

}

bool megaman::loadSprite()
{
bool success = true;

if( !gMegamanTexture.loadFromFile("./dot.bmp"))
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
                        case  SDLK_UP: megamanY_vel -= MEGAMAN_SPEED; break;
                        case  SDLK_DOWN: megamanY_vel += MEGAMAN_SPEED; break;
                        case  SDLK_LEFT: megamanX_vel -= MEGAMAN_SPEED; break;
                        case  SDLK_RIGHT: megamanX_vel += MEGAMAN_SPEED; break;
                }
        }
        if( e.type == SDL_KEYUP && e.key.repeat == 0 )
        {
                switch( e.key.keysym.sym )
                {
                        case  SDLK_UP: megamanY_vel += MEGAMAN_SPEED; break;
                        case  SDLK_DOWN: megamanY_vel -= MEGAMAN_SPEED; break;
                        case  SDLK_LEFT: megamanX_vel += MEGAMAN_SPEED; break;
                        case  SDLK_RIGHT: megamanX_vel -= MEGAMAN_SPEED; break;
                }
        }
}

void megaman::move()
{
	if(megamanX+megamanX_vel >= 0 && megamanX+megamanX_vel < 640)
        	megamanX += megamanX_vel;

        if(megamanY+megamanY_vel >= 0 && megamanY+megamanY_vel < 480)
	        megamanY += megamanY_vel;
}

void megaman::render()
{
        gMegamanTexture.render( megamanX, megamanY );
}

