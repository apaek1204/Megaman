#ifndef STAGE_H
#define STAGE_H
#include <iostream>
#include "LTexture.h"

using namespace std;

class Stage {

	public:
	
	Stage();

//	~Stage();
	
	bool loadSprite();

	void Render(float, float);

	private:

	LTexture* gStageTexture;
	
	LTexture* gBackTexture;
};

Stage::Stage(){

	gStageTexture = new LTexture(15378,1696);
	gBackTexture = new LTexture(7128,744);

}

bool Stage::loadSprite()
{
bool success = true;

if( !gStageTexture->loadFromFile("./../assets/IntroStage/megaman_x1_intro_stage_by_darksamus993.png"))
{
        printf( "Unable to load stage texture! \n");
        success = false;
}

if( !gBackTexture->loadFromFile("./../assets/IntroStage/background.png"))
{
        printf( "Unable to load background texture! \n");
        success = false;
}

return success;
}

void Stage::Render(float camx, float camy){

float newstagex, newstagey;

newstagex = 0 - camx;
newstagey = 0 - camy;
gBackTexture->render(0,0);
gStageTexture->render(newstagex,newstagey);

}
#endif
