#ifndef COINS_HEADER
#define COINS_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>

#include "SpriteSheet.h"
#include "ScrollableEntity.h"
#include "SDLHelper.h"
#include "Score.h"

/*
 * Coin class
 * Updates positions of and renders list of coins
 */
class Coins : public ScrollableEntity {
public:
  Coins(SpriteSheet *tileSheet, Score *score, const SDLHelper *helper);
  ~Coins();
  void render(SDL_Renderer *renderer);
  void shift(int xShift, int yShift);
  struct CoinData{
    SDL_Rect box;
    bool hit;
    int frame_num;
  };
  void generateCoin();
  void handleCollisions(const SDL_Rect *box);
private:
  void addCoin(int x, int y);
  void renderCoin(CoinData data, SDL_Renderer *renderer);
  std::list<CoinData> coins;
  SpriteSheet *tileSheet;
  const SDLHelper *helper;
  Score *score;
  int min_coin_height;
  int max_coin_height;
  int min_gap;
  int max_gap;
  int max_sequence_length;
  int sequence_spacing;
  int point_value;
};

#endif
