#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class SpriteSheet
{
public:
  //Initializes variables
  SpriteSheet();

  //Deallocates memory
  ~SpriteSheet();

  //Loads image at specified path
  bool loadFromFile( std::string path, SDL_Renderer* renderer);

  //Renders texture at given point
  void renderSprite( int screenX, int screenY, SDL_Renderer* renderer, int spriteNumber);

  //Gets image dimensions
  int getWidth();
  int getHeight();

private:
  //The actual hardware texture
  SDL_Texture* mTexture;

  //Sprite size
  int mWidth;
  int mHeight;
};
#endif
