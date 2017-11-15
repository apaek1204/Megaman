// Final Project
// RestartMenu.h

#ifndef RESTARTMENU_H
#define RESTARTMENU_H

#include <iostream>
#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RestartMenu{
	public:
		RestartMenu();				// constructor
		bool loadSprite(); 			// load the menu image
		void Render(void);			// render menu
		
		bool handle_event(SDL_Event& e );	// handle events

	private:
		LTexture* gBackTexture;			// Texture

};

// constructor
RestartMenu::RestartMenu(){
	gBackTexture = new LTexture(640, 480);
}

// Load restart media
bool RestartMenu::loadSprite()
{
	bool success = true;

	if( !gBackTexture->loadFromFile("./../assets/Restart/Restart.png")){
        	printf( "Unable to load restart menu texture! \n");
        	success = false;
	}

return success;
}

// Render
void RestartMenu::Render(void){
	gBackTexture->render(0, 0);

}

// handle events
bool RestartMenu::handle_event(SDL_Event& e){

	cout << "Handling event! " << e.type << endl;
	cout << "SDLK_s is " << SDLK_s << endl;
	// if user presses s, return true and restart game
	if (e.type == 771)
		return false;
	else
		return true;
}

#endif 

