#ifndef OBSTACLES_HEADER
#define OBSTACLES_HEADER
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "spriteSheet.h"
#include <list>

class Obstacles{
public:
  Obstacles(SpriteSheet *tileSheet);
  ~Obstacles();
  void render(SDL_Renderer *renderer);
  void shiftObstacles(int xShift, int yShift);
  struct ObstacleData{
    int x;
    int y;
    int length; // in tiles
    int height; // in tiles
    int tile_num;
  };
  void addObstacle(ObstacleData data);
private:
  SpriteSheet *tileSheet;
  std::list<ObstacleData> obstacles;
  void renderObstacle(ObstacleData data, SDL_Renderer *renderer);
};

#endif
