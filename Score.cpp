#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Score.h"
#include "SDLHelper.h"
#include "SpriteSheet.h"

Score::Score(SpriteSheet* score_sheet, SDLHelper helper, int num_digits, int points_per_frame, int x_from_right, int y_from_top):sprite_sheet(score_sheet), digits(num_digits), ppf(points_per_frame), x_offset(helper.getScreenWidth() - x_from_right), y_offset(y_from_top){
  current_score = 0;
}
Score::~Score(){}

void Score::render(SDL_Renderer *renderer){
  int score = current_score;
  int x = x_offset;
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