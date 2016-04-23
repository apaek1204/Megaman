#ifndef MAINMENU_H
#define MAINMENU_H
#include <iostream>
#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class MainMenu{
	public:
		MainMenu();				// constructor
		bool loadSprite(); 			// load the menu image
		void Render(void);			// render menu
		
		bool handle_event(SDL_Event& e );	// handle events

	private:
		LTexture* gBackTexture;			// Texture

};

// constructor
MainMenu::MainMenu(){
	gBackTexture = new LTexture(640, 480);
}

// Load menu media
bool MainMenu::loadSprite()
{
	bool success = true;

	if( !gBackTexture->loadFromFile("./../assets/MainMenu/MainMenu.png")){
        	printf( "Unable to load background texture! \n");
        	success = false;
	}

return success;
}

// Render
void MainMenu::Render(void){
	gBackTexture->render(0, 0);

}

// handle events
bool MainMenu::handle_event(SDL_Event& e){
	// if user presses s, return true and start game
	if (e.type == SDLK_s)
		return true;
}

#endif 
