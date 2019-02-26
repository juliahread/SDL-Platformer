#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "SpriteSheet.h"

/*
 * Character class
 * Loads, renders, and moves character sprite
 */
class Character {
  public:
    Character(SpriteSheet *charSheet);
    ~Character();
    void render(SDL_Renderer *renderer);
    void jump();
  private:
    Texture* m_bg_texture;
    int m_speed;
    int m_x;
    int m_y;
};

#endif
