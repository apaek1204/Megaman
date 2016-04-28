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

		~megaman();

		bool handleEvent( SDL_Event& e );
		
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
		
		int getcharge_time(void);
		
		int total_time;

		void setHealth( int );    

		void setX_vel( float );
	
		void setY_vel( float );

		float getX_vel();

		void setishit(bool);
		
		bool getishit();

		void setX(int);
    
		void setY(int);
			
		const SDL_Rect getHitBox();

		void subtractHealth(int);

		int getHealth();
		
		void setInvul(int);
		
		int getInvul();
		
		void setJumpFalse();

		void setDir(int);
		
//		void fire();

		bool charging;		// set to know if the shot is still charging
		
		void setcharge_time(int);

	private:

		bool fire;
		bool ishit;
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
		int health;
		int invulnerable;
};



megaman::megaman(float xCoord, float yCoord){
	//constructor
	LTexture* tmp = NULL;

	for( int i = 0; i < 24; i++){
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

	health=10;

	invulnerable = 0;

	charging=false;
	
	total_time=0;

	ishit = false;

}

megaman::~megaman(){
	//destructor
	for( int i = 0; i < 19; i++)
		delete gMegamanTexture[i];
}

bool megaman::loadSprite(){
	//load sprite
	bool success = true;

	if( !gMegamanTexture[0]->loadFromFile("./../assets/sprites/megaman/movement/11.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[1]->loadFromFile("./../assets/sprites/megaman/movement/12.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[2]->loadFromFile("./../assets/sprites/megaman/movement/13.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[3]->loadFromFile("./../assets/sprites/megaman/movement/14.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[4]->loadFromFile("./../assets/sprites/megaman/movement/15.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[5]->loadFromFile("./../assets/sprites/megaman/movement/16.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[6]->loadFromFile("./../assets/sprites/megaman/movement/17.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[7]->loadFromFile("./../assets/sprites/megaman/movement/18.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[8]->loadFromFile("./../assets/sprites/megaman/movement/19.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[9]->loadFromFile("./../assets/sprites/megaman/movement/20.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[10]->loadFromFile("./../assets/sprites/megaman/movement/34.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[11]->loadFromFile("./../assets/sprites/megaman/movement/28.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[12]->loadFromFile("./../assets/sprites/megaman/movement/29.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[13]->loadFromFile("./../assets/sprites/megaman/movement/30.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[14]->loadFromFile("./../assets/sprites/megaman/movement/31.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[15]->loadFromFile("./../assets/sprites/megaman/movement/32.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[16]->loadFromFile("./../assets/sprites/megaman/movement/33.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[17]->loadFromFile("./../assets/sprites/megaman/movement/34.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[18]->loadFromFile("./../assets/sprites/megaman/movement/42.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[19]->loadFromFile("./../assets/sprites/megaman/take_dmg/2.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[20]->loadFromFile("./../assets/sprites/megaman/take_dmg/3.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[21]->loadFromFile("./../assets/sprites/megaman/take_dmg/4.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[22]->loadFromFile("./../assets/sprites/megaman/take_dmg/5.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}
	if( !gMegamanTexture[23]->loadFromFile("./../assets/sprites/megaman/take_dmg/6.png")){
		printf( "Unable to load megaman texture! \n");
		success = false;
	}

	return success;
}

void megaman::setHealth( int newhealth ){
	health = newhealth;
}
bool megaman::handleEvent( SDL_Event& e ){
	//handles any keypresses
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && health > 0){
			//keydowns
            switch( e.key.keysym.sym ){
                case  SDLK_UP: 
					if (megamanY + MEGAMAN_HEIGHT > 200.0){
						if(!JUMPING){
							megamanY_vel = -MEGAMAN_SPEED-7.0; 
							JUMPING = true;
							ONWALL_RIGHT = false;
							ONWALL_LEFT = false;
						}
					}
					break;
				case  SDLK_LEFT: megamanX_vel = -MEGAMAN_SPEED; MOVING = true; DIRECTION = 0; break;
				case  SDLK_RIGHT: megamanX_vel = MEGAMAN_SPEED; DIRECTION = 1; MOVING = true;break;
				case  SDLK_SPACE: fire = true; charging=true; 
					start_time = SDL_GetTicks();   total_time=total_time+SDL_GetTicks();
					break;
            }
        }
        if( e.type == SDL_KEYUP && e.key.repeat == 0 && health > 0){
			//keyups
			switch( e.key.keysym.sym ){
				case  SDLK_UP: if(JUMPING) megamanY_vel = 0; //JUMPING = false;
				break;
				case  SDLK_LEFT: 
					if(megamanX_vel < 0){
						megamanX_vel = 0;
						MOVING = false;
					}
				break;
				case  SDLK_RIGHT: 
					if(megamanX_vel > 0){
						MOVING = false;
						megamanX_vel = 0;
					}

				break;
				case  SDLK_SPACE: end_time = SDL_GetTicks(); total_time=total_time+SDL_GetTicks();
					charge_time = end_time - start_time; charging=false;
					if( charge_time >= 650){
						chargefire = true;
					}
				break;
			}
        }
        return JUMPING;
}

void megaman::setonwall(int whichwall){
	if(whichwall == 1)
		ONWALL_RIGHT = true;
	if(whichwall == 0)
		ONWALL_LEFT = true;
}
void megaman::setchargedfire(bool charged){
	chargefire = charged;
}	
float megaman::getX(){
	return(megamanX);
}

float megaman::getY(){
        return(megamanY);
}

int megaman::getdir(){
        return(DIRECTION);
}

bool megaman::getfire(){
        return fire;
}

bool megaman::getchargedfire(){
	return chargefire;
}

void megaman::move(){
	if( health <= 0 ){
		megamanX_vel=0;
		megamanY_vel=0;
	}
	fire=false;
	if(megamanX+megamanX_vel >= 0 && megamanX+megamanX_vel < 5760){
		megamanX += megamanX_vel;
		circleBox.x += megamanX_vel;
	}
	if(megamanY+megamanY_vel >= 0 && megamanY+megamanY_vel < 1000){
		megamanY += megamanY_vel;
	}
	if (megamanY < 1000){
		megamanY_vel +=.75; 
    	circleBox.y += megamanY_vel;
	}
}

void megaman::render( float camx, float camy, int frame){
	//renders sprites
	float newmegamanX, newmegamanY;
	bool STOP;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	if(DIRECTION == 0){
		flip = SDL_FLIP_HORIZONTAL;
	}
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
	else if (ishit){
		gMegamanTexture[((frame % 12)/3) + 19]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL,  flip);
	}
	else if(JUMPING){
		if( (frame % 21)/3 <  4 && !STOP){
			gMegamanTexture[(frame % 21)/3 + 10]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL,  flip);
		}
		else{
			gMegamanTexture[16]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL, flip);
		}
	}

	else if( MOVING ){
		gMegamanTexture[((frame % 30))/3]->render( newmegamanX, newmegamanY , NULL, 0.0, NULL, flip);
	}
	else{
		gMegamanTexture[10]->render( newmegamanX, newmegamanY, NULL, 0.0, NULL,flip);
	}
}

const SDL_Rect megaman::getHitBox(){
	return circleBox;
}
void megaman::setX(int x){
	megamanX = x;
	circleBox.x = x;
}
void megaman::setY(int y){
	megamanY=y;
	megamanY_vel = 0;
	circleBox.y = megamanY;
}
void megaman::subtractHealth(int a){
	if(int(SDL_GetTicks()) > invulnerable+1000)
		health = health-a;
}
int megaman::getHealth(){
	return health;
}
void megaman::setInvul(int a){
	invulnerable = a;
}
int megaman::getInvul(){
	return invulnerable;
}

int megaman::getcharge_time(){
	return charge_time;
}

void megaman::setcharge_time(int i){
	charge_time=i;
}

void megaman::setX_vel( float newvel ){
	megamanX_vel = newvel;
}

void megaman::setY_vel( float newvel ){
	megamanY_vel = newvel;
}

float megaman::getX_vel(){
	return megamanX_vel;
}
void megaman::setishit( bool newishit ){
	ishit = newishit;
}

bool megaman::getishit(){
	return ishit;
}
void megaman::setJumpFalse(){
	JUMPING=false;
}
void megaman::setDir(int a){
	DIRECTION = a;
}
#endif
