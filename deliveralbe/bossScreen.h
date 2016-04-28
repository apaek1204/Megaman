// Final Project- MegaMan
// Nick Smith, Andrew Paek, and Ashley Cummins
// bossScreen.h, class for the screen when boss is killed

#ifndef BOSSSCREEN_H
#define RESTARTMENU_H

// include libraries
#include <iostream>
#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// define bossScreen class
class bossScreen{
	public:
		bossScreen();				// constructor
		bool loadSprite(); 			// load the menu image
		void Render(void);			// render menu
		
		bool handle_event(SDL_Event& e );	// handle events

	private:
		LTexture* gBackTexture;			// Texture

};

// constructor
bossScreen::bossScreen(){
	gBackTexture = new LTexture(640, 480);
}

// Load bossScreen media
bool bossScreen::loadSprite()
{
	bool success = true;

	if( !gBackTexture->loadFromFile("./../assets/bossScreen/bossScreen.png")){
        	printf( "Unable to load boss screen texture! \n");
        	success = false;
	}

	return success;
}

// Render
void bossScreen::Render(void){
	gBackTexture->render(0, 0);

}

// handle events
bool bossScreen::handle_event(SDL_Event& e){
	 //if user presses s, return false and restart game
	if (( e.type > 750 ) && (e.type < 800))
		return false;
	else
		return true;
}

#endif 
