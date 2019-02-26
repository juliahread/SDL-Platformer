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
    Character(SpriteSheet* char_sheet, int speed, int x, int y);
    ~Character();
    void render(SDL_Renderer* renderer);
    void jump();
  private:
    SpriteSheet* m_char_sheet;
    int m_speed;
    int m_x;
    int m_y;
    int m_ground;
    int m_frame_number;
    int m_iteration;
};

#endif
