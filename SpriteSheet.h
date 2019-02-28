#ifndef SPRITE_SHEET_HEADER
#define SPRITE_SHEET_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Texture.h"

/*
 * SpriteSheet class
 * Loads and renders equally sized sprites from one image
 */
class SpriteSheet {
  public:
    //Initializes variables
    SpriteSheet();
    //Deallocates memory
    ~SpriteSheet();
    //Loads image at specified path
    bool loadFromFile( std::string path, SDL_Renderer* renderer, int num_sprites);
    //Renders texture at given point
    void renderSprite( int screenX, int screenY, SDL_Renderer* renderer, int spriteNumber);
  void renderSubSprite( int screenX, int screenY, SDL_Renderer* renderer, int spriteNumber, SDL_Rect frame);
    //Gets image dimensions
    int getWidth();
    int getHeight();
  private:
    //Texture wrapper class
    Texture *texture;
    //Sprite size
    int spriteWidth;
    int spriteHeight;
    //For calculating dimensions
    int numSprites;
};

#endif
