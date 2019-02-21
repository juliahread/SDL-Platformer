#include "spriteSheet.h"
#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SpriteSheet::SpriteSheet()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

SpriteSheet::~SpriteSheet()
{
	//Deallocate texture
  mTexture.~Texture();
}

bool SpriteSheet::loadFromFile( std::string path, SDL_Renderer* renderer)
{
  Texture mTexture();
  mTexture.loadFromFile(path, renderer);
}

void SpriteSheet::renderSprite( int screenX, int screenY, SDL_Renderer* renderer, int spriteNumber)
{
  SDL_Rect coords = { spriteNumber * mWidth, 0, mWidth, mHeight };
  mTexture.render(screenX, screenY, renderer, coords);
}

int SpriteSheet::getWidth()
{
	return mWidth;
}

int SpriteSheet::getHeight()
{
	return mHeight;
}
