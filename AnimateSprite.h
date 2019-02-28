#ifndef ANIMATION_TEST_HEADER
#define ANIMATION_TEST_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SpriteSheet.h"

/*
 * AnimateSprite class
 * TODO: add more details
 */
class AnimateSprite {
  public:
    AnimateSprite(SpriteSheet* sheet, int speed);
    ~AnimateSprite();
    void render(int x, int y, SDL_Renderer* renderer);
  private:
    SpriteSheet* m_sheet;
    int m_frame_number;
    int m_iteration;
    int m_speed;
};

#endif
