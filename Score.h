#ifndef SCORE_HEADER
#define SCORE_HEADER
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SpriteSheet.h"
#include "SDLHelper.h"

/*
 * Score class
 * Calculates and renders the player's score
 */
class Score {
public:
  Score(SpriteSheet* score_sheet, int num_digits, int points_per_frame, bool measure_from_left, int x_offset, int y_from_top, const SDLHelper *helper);
  ~Score();
  void render(SDL_Renderer *renderer);
  void update();
  void increase(int points);
  int getScore();
private:
  int current_score;
  SpriteSheet *sprite_sheet;
  int digits;
  int ppf;
  int x_offset;
  int y_offset;
};
#endif
