#include <SDL2/SDL.h>

#include "Coins.h"

static const int MIN_COIN_HEIGHT = 100;
static const int MIN_GAP = 400;
static const int MAX_GAP = 1000;
static const int MAX_SEQUENCE_LENGTH = 5;
static const int SEQUENCE_SPACING = 25;
static const int POINT_VALUE = 50;
static const int COIN_ROTATION_FRAMES = 6;


Coins::Coins(SpriteSheet *tileSheetArg, Score *scoreArg, const SDLHelper *helperArg): helper(helperArg), tileSheet(tileSheetArg), score(scoreArg), min_coin_height(MIN_COIN_HEIGHT), min_gap(MIN_GAP), max_gap(MAX_GAP), max_sequence_length(MAX_SEQUENCE_LENGTH), sequence_spacing(SEQUENCE_SPACING), point_value(POINT_VALUE){
  max_coin_height = helper->getScreenHeight() - 100;
  std::list <CoinData> coins;
}

Coins::~Coins(){}

void Coins::render(SDL_Renderer *renderer){
  for (auto it = coins.begin(); it != coins.end(); it++){
    renderCoin(*it, renderer);
  }
}

void Coins::shift(int xShift, int yShift) {
  for (auto it = coins.begin(); it != coins.end(); ++it) {
    if(!it->hit){
      it->box.x -= xShift;
      it->box.y -= yShift;
    } else {
      it->box.y -= 20;
    }
    it->frame_num = (it->frame_num + 1) % COIN_ROTATION_FRAMES;
    if ((it->box.x + it->box.w) < 0 or
        (it->box.y + it->box.h) < 0) {
      it = coins.erase(it);
      it--;
    }
  }
}

//TODO: move magic numbers to member variables and add generate to parent class
void Coins::generateCoin(){
  int last_x;
  if (coins.empty()){
    last_x = helper->getScreenWidth();
  } else {
    CoinData lastObstacle = *(--coins.end());
    last_x = lastObstacle.box.x + lastObstacle.box.w;
  }
  while (last_x <= helper->getScreenWidth()){
    int gap = min_gap + (rand() % (max_gap - min_gap));
    int new_y = min_coin_height + (rand() % (max_coin_height - min_coin_height));
    int sequence_length = 1 + rand() % (max_sequence_length - 1);
    int offset = tileSheet->getWidth() + sequence_spacing;
    for (int i = 0; i < sequence_length; i++){
      addCoin((last_x + gap) + (i * offset), new_y);
    }
    CoinData lastObstacle = *(--coins.end());
    last_x = lastObstacle.box.x + lastObstacle.box.w;
  }
}

void Coins::handleCollisions(const SDL_Rect *box){
  for (auto it = coins.begin(); it != coins.end(); it++){
    if (!it->hit and SDL_HasIntersection(box, &(it->box))){
      score->increase(point_value);
      it->hit = true;
    }
  }
}

void Coins::addCoin(int x, int y){
  CoinData data;
  data.box.x = x;
  data.box.y = y;
  data.box.w = tileSheet->getWidth();
  data.box.h = tileSheet->getHeight();
  data.frame_num = 0;
  data.hit = false;
  coins.push_back(data);
}

void Coins::renderCoin(CoinData data, SDL_Renderer *renderer){
  tileSheet->renderSprite(data.box.x, data.box.y, renderer, data.frame_num);
}
