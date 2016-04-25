#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

// ONPARE3_00003.wav <- him appearing
// ST07__00_00006.wav <- bee

class music{
	public:
		bool Load_music();			// load music
		void close_music();			// close the music file
		Mix_Music *mMusic = NULL;		// constant music that will be played during game
		Mix_Music *mmMusic=NULL;		// constant main menu music
		
		Mix_Chunk *lMusic = NULL;		// laser sound effect
		Mix_Chunk *clMusic=NULL;		// charged shot sound effect
		
		Mix_Chunk *newlifeMusic=NULL;		// sound effect when new game starts
		
		Mix_Chunk *jumpingMusic=NULL;		// sound effect when mega man jumps
		
		Mix_Chunk
		
};

// Load the music
bool music::Load_music(void){
	bool success= true;
	//Load main music
	mMusic = Mix_LoadMUS( "./../assets/music/centralhighway.wav" );
	if( mMusic == NULL )
	{
		printf( "Failed to load main music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	// load main menu music
	mmMusic=Mix_LoadMUS("./../assets/music/mainmenuX.wav");
	if( mmMusic == NULL )
	{
		printf( "Failed to load main menu music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	// load sound effect for laser
	lMusic = Mix_LoadWAV( "./../assets/music/soundEffects/ONPARE3_00001.wav" );
	if( lMusic == NULL )
	{
		printf( "Failed to load laser sound effect music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	// load sound effect for charged shot
	clMusic=Mix_LoadWAV("./../assets/music/soundEffects/ONPARE3_00002.wav");
	if ( clMusic == NULL)
	{
		printf( "Failed to load charged laser sound effect music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	// load sound effect for new game
	newlifeMusic=Mix_LoadWAV("./../assets/music/soundEffects/ONPARE3_00008.wav");
	if ( newlifeMusic == NULL)
	{
		printf( "Failed to load new game sound effect music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	// load sound effect for jumping
	jumpingMusic=Mix_LoadWAV("./../assets/music/soundEffects/PL01_U_00038.wav");
	if ( jumpingMusic == NULL)
	{
		printf( "Failed to load jumping sound effect music! SDL_mixer Error: %s\n", Mix_GetError() );
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
	mmMusic=NULL;
	
	// Free sound effects
	Mix_FreeChunk(lMusic);
	lMusic=NULL;
	Mix_FreeChunk(clMusic);
	clMusic=NULL;
	Mix_FreeChunk(newlifeMusic);
	newlifeMusic=NULL;
	Mix_FreeChunk(jumpingMusic);
	jumpingMusic=NULL;
}

# endif 
