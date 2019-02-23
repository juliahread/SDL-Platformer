#ifndef ANIMATION_TEST_HEADER
#define ANIMATION_TEST_HEADER
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "spriteSheet.h"

class AnimationTest{
public:
  AnimationTest(SpriteSheet *sheet1);
  ~AnimationTest();
  void render(SDL_Renderer *renderer);
private:
  SpriteSheet *sheet;
  int frame_number;
};
#endif
