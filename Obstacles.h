#ifndef OBSTACLES_HEADER
#define OBSTACLES_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>

#include "SpriteSheet.h"

/*
 * Obstacle class
 * Updates positions of and renders list of Obstacles
 */
class Obstacles {
  public:
    Obstacles(SpriteSheet *tileSheet);
    ~Obstacles();
    void render(SDL_Renderer *renderer);
    void shiftObstacles(int xShift, int yShift);
    struct ObstacleData{
      SDL_Rect box;
      int tile_num;
    };
  void generateObstacle(int min_gap, int max_gap, int max_dy, int screen_width, int screen_height);
  std::list <SDL_Rect*> detectCollisions(SDL_Rect *boundingBox);
  private:
    void addObstacle(ObstacleData data);
    void addObstacle(int x, int y, int length, int height, int tile_num);
    SpriteSheet *tileSheet;
    std::list<ObstacleData> obstacles;
    void renderObstacle(ObstacleData data, SDL_Renderer *renderer);
};

#endif
