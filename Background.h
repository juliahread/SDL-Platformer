#ifndef BACKGROUND_HEADER
#define BACKGROUND_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Texture.h"

/*
 * Background class
 * Loads and renders background texture
 */
class Background {
  public:
    Background();
    ~Background();
    void render(SDL_Renderer *renderer);
  private:
    Texture* m_bg_texture; //TODO: make list of bg textures
    int m_speed;
    int m_x;
    int m_y;
};

#endif
