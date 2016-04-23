#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

class music{
	public:
		bool Load_music();			// load music
		void close_music();			// close the music file
		Mix_Music *mMusic = NULL;		// music that will be played
		
};

// Load the music
bool music::Load_music(void){
	bool success= true;
	//Load music
	mMusic = Mix_LoadMUS( "./../assets/music/bombman.wav" );
	if( mMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	return success;
}

// close music files
void music::close_music(void){
	Mix_FreeMusic(mMusic);
	mMusic=NULL;
}

# endif 
