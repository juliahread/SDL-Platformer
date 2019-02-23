#include "spriteSheet.h"
#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SpriteSheet::SpriteSheet()
{
	//Initialize
	texture = nullptr;
	spriteWidth = 0;
	spriteHeight = 0;
}

SpriteSheet::~SpriteSheet()
{
	//Deallocate texture
  texture->~Texture();
}

bool SpriteSheet::loadFromFile(std::string path, SDL_Renderer* renderer, int num_sprites)
{
  texture = new Texture();
  bool success = texture->loadFromFile(path, renderer);
  if (success){
    numSprites = num_sprites;
    spriteWidth = texture->getWidth() / numSprites;
    spriteHeight = texture->getHeight();
  }
  return success;
}

void SpriteSheet::renderSprite( int screenX, int screenY, SDL_Renderer* renderer, int frameNumber)
{
  int spriteNumber = frameNumber % numSprites;
  SDL_Rect coords = { spriteNumber * spriteWidth, 0, spriteWidth, spriteHeight };
  texture->render(screenX, screenY, renderer, &coords);
}

int SpriteSheet::getWidth()
{
	return spriteWidth;
}

int SpriteSheet::getHeight()
{
	return spriteHeight;
}
