#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Score.h"
#include "SpriteSheet.h"
#include "SDLHelper.h"

Score::Score(SpriteSheet* score_sheet, int num_digits, int points_per_frame, bool measure_from_left, int x_dist, int y_from_top, const SDLHelper *helper):sprite_sheet(score_sheet), digits(num_digits), ppf(points_per_frame), y_offset(y_from_top){
  current_score = 0;
  if (not measure_from_left){
    x_offset = helper->getScreenWidth() - (num_digits * score_sheet->getWidth()) - x_dist;
  } else {
    x_offset = x_dist;
  }
}
Score::~Score(){
}

void Score::render(SDL_Renderer *renderer){
  int score = current_score;
  int x = x_offset + digits * sprite_sheet->getWidth();
  for (int d = 0; d < digits; d++){
    int digitVal = score % 10;
    score /= 10;
    x-= sprite_sheet->getWidth();
    sprite_sheet->renderSprite(x, y_offset, renderer, digitVal);
  }
}

void Score::update(){
  current_score += ppf;
}

void Score::increase(int points_gained){
  current_score += points_gained;
}

int Score::getScore(){
  return current_score;
}
