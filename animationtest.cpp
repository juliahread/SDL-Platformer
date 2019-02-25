#include "spriteSheet.h"
#include "animationtest.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

AnimationTest::AnimationTest(SpriteSheet *sheet1){
  sheet = sheet1;
  frame_number = 0;
}

AnimationTest::~AnimationTest(){
}

void AnimationTest::render(int x, int y, SDL_Renderer *renderer, int iteration){
  if (iteration == 2) {
    sheet->renderSprite(x, y, renderer, frame_number++);
  }
  else {
    sheet->renderSprite(x, y, renderer, frame_number);
  }
}
