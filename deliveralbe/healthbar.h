#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include <vector>
class healthbar{

        public:

                healthbar(float=500, float=400);

		~healthbar();

                bool loadSprite();
	
		void render(float, float, int);

                const SDL_Rect getHitBox();
		
	        void shoot(int);
		
		void setX(int);
                
		void setY(int);




          private:

                vector < LTexture* > gEnemyTexture;
                float enemyX_vel, enemyY_vel;
		float enemyX, enemyY;
		int health;
};

healthbar::healthbar(float xCoord, float yCoord)
{
	LTexture* tmp = NULL;
	for( int i = 0; i < 10; i++ ){
		if(i==0)
			tmp = new LTexture(20,30);
		else
			tmp = new LTexture(i*20,30); 
       		gEnemyTexture.push_back(tmp);
				     }
	
enemyX = xCoord;
health = 10;
enemyY = yCoord;

}

healthbar::~healthbar()
{
	for( int i = 0; i<10; i++)
		delete gEnemyTexture[i];
}
bool healthbar::loadSprite()
{
bool success = true;

for( int i = 0; i<10; i++){
if( !gEnemyTexture[i]->loadFromFile("./../assets/sprites/megaman/healthbar.png"))
{
        printf( "Unable to load enemy texture! \n");
        success = false;
}
}

return success;
}
void healthbar::render( float camx, float camy,int health)
{
float newenemyX, newenemyY;
SDL_RendererFlip flip = SDL_FLIP_NONE;
newenemyX = enemyX - camx;
newenemyY = enemyY - camy;
	if( health >=0)
		gEnemyTexture[health]->render( newenemyX, newenemyY, NULL, 0.0, NULL,flip);
}

void healthbar::setX(int a){
  enemyX = a;
  
}
void healthbar::setY(int a){
  enemyY = a;
}
#endif
