#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>
#include <iterator>

#include "Obstacles.h"

//Obstacle constructor takes in tile sheet
Obstacles::Obstacles(SpriteSheet *tileSheetArg) {
  tileSheet = tileSheetArg;
  std::list <ObstacleData> obstacles;
}

//Obstacle destructor
Obstacles::~Obstacles() {
  //fill in destructor?
}

//Iterates through obstacle list and calls renderObstacle
void Obstacles::render(SDL_Renderer *renderer) {
  std::list <ObstacleData> :: iterator it;
  for (it = obstacles.begin(); it != obstacles.end(); ++it) {
    renderObstacle(*it, renderer);
  }
}

//Renders a given obstacle given its position
void Obstacles::renderObstacle(ObstacleData data, SDL_Renderer *renderer) {
  for (int dy = 0; dy < data.box.h; dy += tileSheet->getHeight()) {
    for (int dx = 0; dx < data.box.w; dx += tileSheet->getWidth()) {
      int screenX = data.box.x + dx;
      int screenY = data.box.y + dy;
      SDL_Rect frame;
      frame.w = std::min(tileSheet->getWidth(), data.box.w - dx);
      frame.h = std::min(tileSheet->getHeight(), data.box.h - dy);
      tileSheet->renderSubSprite(screenX, screenY, renderer, data.tile_num, frame);
    }
  }
}

//Iterates through obstacles and shifts their positions
void Obstacles::shiftObstacles(int xShift, int yShift) {
  std::list <ObstacleData> :: iterator it;
  for (it = obstacles.begin(); it != obstacles.end(); ++it) {
    it->box.x -= xShift;
    it->box.y -= yShift;
    if ((it->box.x + tileSheet->getWidth() * it->box.w) < 0 or
        (it->box.y + tileSheet->getHeight() * it->box.h) < 0) {
      it = obstacles.erase(it);
      it--;
    }
  }
}

//Adds a new obstacle to the obstacle list
void Obstacles::addObstacle(Obstacles::ObstacleData data) {
  obstacles.push_back(data);
}

void Obstacles::addObstacle(int x, int y, int width, int height, int tile_num) {
  Obstacles::ObstacleData data;
  SDL_Rect box;
  box.x = x;
  box.y = y;
  box.w = width;
  box.h = height;
  data.tile_num = tile_num;
  data.box = box;
}

std::list <SDL_Rect*> Obstacles::detectCollisions(SDL_Rect *boundingBox){
  std::list <SDL_Rect*> colliding_obstacles;
  for (auto it = obstacles.begin(); it != obstacles.end(); ++it){
    if (SDL_HasIntersection(&(it->box), boundingBox)){
      colliding_obstacles.push_back(&(it->box));
    }
  }
  return colliding_obstacles;
}

