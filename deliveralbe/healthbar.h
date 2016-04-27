#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include <vector>
class healthbar{

        public:

                healthbar();

                void render( int);

                bool loadSprite();

	private:

		LTexture* gHealthTexture;
		int health;
};

healthbar::healthbar()
{

LTexture* gHealthTexture = new LTexture(50,100);
health = 10;

}

bool healthbar::loadSprite()
{
bool success = true;

if( !gHealthTexture->loadFromFile("./../assets/sprites/megaman/healthbar.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
}

void healthbar::render(int health)
{
       gHealthTexture->render( 50, 50,NULL,0.0,NULL);
}
#endif
