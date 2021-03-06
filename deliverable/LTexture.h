#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class LTexture
{
        public:

                LTexture(int=0, int=0);

                ~LTexture();

                bool loadFromFile( std::string path );

                void free();

                void setColor( Uint8 red, Uint8 green, Uint8 blue );

                void setBlendMode( SDL_BlendMode blending );

                void setAlpha( Uint8 alpha );

                void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

                int getWidth();
                int getHeight();

        private:

                SDL_Texture* mTexture;

                int mWidth;
                int mHeight;
};


LTexture::LTexture(int w, int h)
{
        mTexture = NULL;
        mWidth = w;
        mHeight = h;
}

LTexture::~LTexture()
{
        free();
}

bool LTexture::loadFromFile( std::string path )
{
        free();

        SDL_Texture* newTexture = NULL;

        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == NULL )
        {
                printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        }
        else
        {
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( newTexture == NULL )
                {
                        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
                }
               if(mWidth == 0 && mHeight == 0)  
               {
                        mWidth = loadedSurface->w;
                        mHeight = loadedSurface->h;
                }

                SDL_FreeSurface( loadedSurface );
        }

                mTexture = newTexture;
                        return mTexture != NULL;
                        }

void LTexture::free()
{
        if( mTexture != NULL )
        {
                SDL_DestroyTexture( mTexture );
                mTexture = NULL;
                mWidth = 0;
                mHeight = 0;
        }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
        SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
        SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
        SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };

        if( clip != NULL )
        {
                renderQuad.w = clip->w;
                renderQuad.h = clip->h;
        }

        SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
        return mWidth;
}

int LTexture::getHeight()
{
        return mHeight;
}
#endif                       
