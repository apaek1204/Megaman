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
		Mix_Music *mMusic = NULL;		// constant music that will be played during game
		Mix_Music *mmMusic=NULL;		// constant main menu music
		
		Mix_Chunk *lMusic = NULL;		// laser sound effect
		
};

// Load the music
bool music::Load_music(void){
	bool success= true;
	//Load main music
	mMusic = Mix_LoadMUS( "./../assets/music/bombman.wav" );
	if( mMusic == NULL )
	{
		printf( "Failed to load main music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	// load main menu music
	mmMusic=Mix_LoadMUS("./../assets/music/mainmenu10.wav");
	if( mmMusic == NULL )
	{
		printf( "Failed to load main menu music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	// load sound effects
	lMusic = Mix_LoadWAV( "./../assets/music/soundEffects/ONPARE3_00001.wav" );
	if( lMusic == NULL )
	{
		printf( "Failed to load laser sound effect music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	
	return success;
}

// close music files
void music::close_music(void){
	// Free music
	Mix_FreeMusic(mMusic);
	mMusic=NULL;
	Mix_FreeMusic(mmMusic);
	
	// Free sound effects
	Mix_FreeChunk(lMusic);
	lMusic=NULL;
}

# endif 
