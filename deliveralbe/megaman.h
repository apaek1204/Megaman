#ifndef MEGAMAN_H
#define MEGAMAN_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "laser.h"
#include <vector>
class megaman{

	public:

		static const int MEGAMAN_WIDTH = 70;
		static const int MEGAMAN_HEIGHT = 70;
		
		static const float MEGAMAN_SPEED = 5;

		megaman(float=500, float=0);

		void handleEvent( SDL_Event& e );
		
		void move();

		void render(float , float, int);

		bool loadSprite();		

		bool getfire();
	
		float getX();

		float getY();

		int getdir();
		
    const SDL_Rect getHitBox();
//		void fire();

	private:

		bool fire;

		vector< LTexture* > gMegamanTexture;
		//LTexture gMegamanTexture;

		float megamanX, megamanY;
		int  DIRECTION;
		bool JUMPING;
		bool MOVING;
		float megamanX_vel, megamanY_vel;
		unsigned int start_time , end_time ;
		unsigned int charge_time;
    SDL_Rect circleBox;
};



megaman::megaman(float xCoord, float yCoord){

LTexture* tmp = NULL;

for( int i = 0; i < 18; i++){
	tmp = new LTexture(70,70);
	gMegamanTexture.push_back(tmp);
}
megamanX = xCoord;

megamanY = yCoord;

MOVING = false;

JUMPING = false;

DIRECTION=0;

fire = false;

megamanX_vel = 0;

megamanY_vel = 0;

circleBox.x = megamanX;

circleBox.y = megamanY;

circleBox.w = MEGAMAN_WIDTH;

circleBox.h = MEGAMAN_HEIGHT;

start_time = 0;

end_time = 0;

charge_time = 0;
}

bool megaman::loadSprite()
{
bool success = true;

if( !gMegamanTexture[0]->loadFromFile("./../assets/sprites/megaman/movement/11.png"))
{
	printf( "Unable to load megaman texture! \n");
	success = false;
}
if( !gMegamanTexture[1]->loadFromFile("./../assets/sprites/megaman/movement/12.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[2]->loadFromFile("./../assets/sprites/megaman/movement/13.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[3]->loadFromFile("./../assets/sprites/megaman/movement/14.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[4]->loadFromFile("./../assets/sprites/megaman/movement/15.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[5]->loadFromFile("./../assets/sprites/megaman/movement/16.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[6]->loadFromFile("./../assets/sprites/megaman/movement/17.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[7]->loadFromFile("./../assets/sprites/megaman/movement/18.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[8]->loadFromFile("./../assets/sprites/megaman/movement/19.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[9]->loadFromFile("./../assets/sprites/megaman/movement/20.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[10]->loadFromFile("./../assets/sprites/megaman/movement/0.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[11]->loadFromFile("./../assets/sprites/megaman/movement/28.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[12]->loadFromFile("./../assets/sprites/megaman/movement/29.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[13]->loadFromFile("./../assets/sprites/megaman/movement/30.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[14]->loadFromFile("./../assets/sprites/megaman/movement/31.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[15]->loadFromFile("./../assets/sprites/megaman/movement/32.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[16]->loadFromFile("./../assets/sprites/megaman/movement/33.png"))
{
        printf( "Unable to load megaman texture! \n");
        success = false;
}
if( !gMegamanTexture[17]->loadFromFile("./../assets/sprites/megaman/movement/34.png"))
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
                        case  SDLK_UP: if (megamanY + MEGAMAN_HEIGHT > 200.0)
						megamanY_vel = -MEGAMAN_SPEED-7.0; 
					JUMPING = true;
						break;
                        case  SDLK_DOWN: megamanY_vel += MEGAMAN_SPEED; break;
                        case  SDLK_LEFT: megamanX_vel -= MEGAMAN_SPEED; MOVING = true; DIRECTION = 0; break;
                        case  SDLK_RIGHT: megamanX_vel += MEGAMAN_SPEED; DIRECTION = 1; MOVING = true;break;
			case  SDLK_SPACE: fire = true; 
					start_time = SDL_GetTicks(); 
						break;
                }
        }
        if( e.type == SDL_KEYUP && e.key.repeat == 0 )
        {
                switch( e.key.keysym.sym )
                {
                        case  SDLK_UP: megamanY_vel = 0; JUMPING = false;
			       break;
                        case  SDLK_DOWN: megamanY_vel -= MEGAMAN_SPEED; break;
                        case  SDLK_LEFT: MOVING = false; megamanX_vel += MEGAMAN_SPEED;  break;
                        case  SDLK_RIGHT: MOVING = false; megamanX_vel -= MEGAMAN_SPEED;  break;
                	case  SDLK_SPACE: end_time = SDL_GetTicks();
				charge_time = end_time - start_time;
			      if( charge_time >= 1000){
					fire = true;
					}
				 break;
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
	if(megamanX+megamanX_vel >= 0 && megamanX+megamanX_vel < 5000){
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

void megaman::render( float camx, float camy, int frame)
{
float newmegamanX, newmegamanY;
newmegamanX = megamanX - camx;
newmegamanY = megamanY - camy;
if(JUMPING){
	frame = 5*frame;
	if( (frame % 28)/4 < 6)
		gMegamanTexture[(frame % 28)/4 + 10]->render( newmegamanX, newmegamanY);
}
else if( MOVING )
	gMegamanTexture[((frame % 30))/3]->render( newmegamanX, newmegamanY );
else
	gMegamanTexture[10]->render( newmegamanX, newmegamanY);
}

const SDL_Rect megaman::getHitBox(){
  return circleBox;
}

#endif
