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
    Background(Texture* bg_texture, int speed);
    ~Background();
    void render(SDL_Renderer *renderer);
    void scroll();
  private:
    Texture* m_bg_texture;
    int m_speed;
    int m_y;
    int m_scrolling_offset;
};

#endif
