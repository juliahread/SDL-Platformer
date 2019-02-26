#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "SpriteSheet.h"
#include "Texture.h"

//SpriteSheet constructor initializes variables
SpriteSheet::SpriteSheet() {
	texture = nullptr;
	spriteWidth = 0;
	spriteHeight = 0;
}

//SpriteSheet destructor deallocates texture
SpriteSheet::~SpriteSheet() {
  texture->~Texture();
}

//Creates SpriteSheet from file given file path
bool SpriteSheet::loadFromFile(std::string path, SDL_Renderer* renderer, int num_sprites) {
  texture = new Texture();
  bool success = texture->loadFromFile(path, renderer);
  if (success){
    numSprites = num_sprites;
    spriteWidth = texture->getWidth() / numSprites;
    spriteHeight = texture->getHeight();
  }
  return success;
}

//Renders correct sprite at given position
void SpriteSheet::renderSprite( int screenX, int screenY, SDL_Renderer* renderer, int frameNumber) {
  int spriteNumber = frameNumber % numSprites;
  SDL_Rect coords = { spriteNumber * spriteWidth, 0, spriteWidth, spriteHeight };
  texture->render(screenX, screenY, renderer, &coords);
}

int SpriteSheet::getWidth() {
	return spriteWidth;
}

int SpriteSheet::getHeight() {
	return spriteHeight;
}
