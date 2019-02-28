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
    SDL_Rect getBoundingBox();
    void updateY();
    bool isJumping();
  private:
    SpriteSheet* m_char_sheet;
    int m_speed;
    int m_ground;
    int m_frame_number;
    int m_iteration;
    SDL_Rect m_box;
    bool m_jumping;
    float m_vel;
    float m_acc;
};

#endif
