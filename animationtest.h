#ifndef ANIMATION_TEST_HEADER
#define ANIMATION_TEST_HEADER
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "spriteSheet.h"

class AnimationTest{
public:
  AnimationTest(SpriteSheet *sheet1);
  ~AnimationTest();
  void render(int x, int y, SDL_Renderer *renderer, int iteration);
private:
  SpriteSheet *sheet;
  int frame_number;
};
#endif
