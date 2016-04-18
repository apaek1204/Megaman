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

	LTexture* gBackTexture;
};

Stage::Stage(){

	gBackTexture = new LTexture(15378,1696);

}

bool Stage::loadSprite()
{
bool success = true;

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
newstagey = 200 - camy;
gBackTexture->render(newstagex,newstagey);

}
#endif
