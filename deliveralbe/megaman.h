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

		void setonwall(int);
	
		float getX();

		float getY();

		int getdir();

		bool getchargedfire();

		void setchargedfire(bool);
    
    void setX(int);
    
    void setY(int);
		
    const SDL_Rect getHitBox();
//		void fire();

	private:

		bool fire;

		vector< LTexture* > gMegamanTexture;
		//LTexture gMegamanTexture;
		bool ONWALL_RIGHT;
		bool ONWALL_LEFT;
		float megamanX, megamanY;
		int  DIRECTION;
		bool JUMPING;
		bool MOVING;
		float megamanX_vel, megamanY_vel;
		unsigned int start_time , end_time ;
		unsigned int charge_time;
		bool chargefire;
    SDL_Rect circleBox;
};



megaman::megaman(float xCoord, float yCoord){

LTexture* tmp = NULL;

for( int i = 0; i < 19; i++){
	tmp = new LTexture(70,70);
	gMegamanTexture.push_back(tmp);
}
megamanX = xCoord;

megamanY = yCoord;

MOVING = false;

JUMPING = false;

DIRECTION=0;

fire = false;

ONWALL_RIGHT = false;

ONWALL_LEFT = false;

megamanX_vel = 0;

megamanY_vel = 0;

circleBox.x = megamanX;

circleBox.y = megamanY;

circleBox.w = MEGAMAN_WIDTH;

circleBox.h = MEGAMAN_HEIGHT;

start_time = 0;

end_time = 0;

charge_time = 0;

chargefire = false;
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
if( !gMegamanTexture[10]->loadFromFile("./../assets/sprites/megaman/movement/34.png"))
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
if( !gMegamanTexture[18]->loadFromFile("./../assets/sprites/megaman/movement/42.png"))
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
					ONWALL_RIGHT = false;
					ONWALL_LEFT = false;
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
			      if( charge_time >= 650){
					chargefire = true;
					}
				 break;
		}
        }
}

void megaman::setonwall(int whichwall)
{
	if(whichwall == 1)
		ONWALL_RIGHT = true;
	if(whichwall == 0)
		ONWALL_LEFT = true;
}
void megaman::setchargedfire(bool charged)
{
	chargefire = charged;
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

bool megaman::getchargedfire()
{
	return chargefire;
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
	if(megamanX+megamanX_vel >= 0 && megamanX+megamanX_vel < 5760){
    megamanX += megamanX_vel;
    circleBox.x += megamanX_vel;
  }
  if(megamanY+megamanY_vel >= 0 && megamanY+megamanY_vel < 1000)
	  megamanY += megamanY_vel;
	  if (megamanY < 1000){
		megamanY_vel +=.75; 
    		circleBox.y += megamanY_vel;
		}
}

void megaman::render( float camx, float camy, int frame)
{
float newmegamanX, newmegamanY;
bool STOP;
SDL_RendererFlip flip = SDL_FLIP_NONE;
if(DIRECTION == 0)
	flip = SDL_FLIP_HORIZONTAL;
newmegamanX = megamanX - camx;
newmegamanY = megamanY - camy;
if(ONWALL_RIGHT){
	flip = SDL_FLIP_NONE;
	gMegamanTexture[18]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL,  flip);
	}
else if(ONWALL_LEFT){
        flip = SDL_FLIP_HORIZONTAL;
        gMegamanTexture[18]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL,  flip);
        }

else if(JUMPING){
	if( (frame % 21)/3 <  4 && !STOP)
		gMegamanTexture[(frame % 21)/3 + 10]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL,  flip);
	/*else if (megamanY + MEGAMAN_HEIGHT < 400){
		STOP = true;
		gMegamanTexture[16]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL, flip);
		}*/
	else
		gMegamanTexture[16]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL, flip);
}
/*else if(megamanY < 400)
	gMegamanTexture[16]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL, flip);
*/
else if( MOVING )
	gMegamanTexture[((frame % 30))/3]->render( newmegamanX, newmegamanY , NULL, 0.0, NULL, flip);
else
	gMegamanTexture[10]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL,flip);
}

const SDL_Rect megaman::getHitBox(){
  return circleBox;
}
void megaman::setX(int x){
  megamanX = x;
  circleBox.x = x;
  //megamanX_vel = 0;
}
void megaman::setY(int y){
  megamanY=y;
  megamanY_vel = 0;
  circleBox.y = megamanY;
}
#endif
