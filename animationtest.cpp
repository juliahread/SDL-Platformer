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

void AnimationTest::render(SDL_Renderer *renderer){
  sheet->renderSprite(0, 0, renderer, frame_number++);
}
