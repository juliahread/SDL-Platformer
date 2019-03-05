#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>
#include <iterator>
#include <algorithm>

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
void Obstacles::shift(int xShift, int yShift) {
  std::list <ObstacleData> :: iterator it;
  for (it = obstacles.begin(); it != obstacles.end(); ++it) {
    it->box.x -= xShift;
    it->box.y -= yShift;
    if ((it->box.x + it->box.w) < 0 or
        (it->box.y + it->box.h) < 0) {
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
  addObstacle(data);
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

void Obstacles::generateObstacle(int min_gap, int max_gap, int max_dy, int screen_width, int screen_height){
  int last_x;
  int last_y;
  if (obstacles.empty()){
    last_x = screen_width - 100;
    last_y = screen_height;
  } else {
    ObstacleData lastObstacle = *(--obstacles.end());
    last_x = lastObstacle.box.x + lastObstacle.box.w;
    last_y = lastObstacle.box.y;
  }
  while (last_x <= screen_width){
    int gap = min_gap + (rand() % (max_gap - min_gap));
    int new_y = last_y + (rand() % (2 * max_dy)) - max_dy;
    new_y = std::max(std::min(new_y, screen_height - 100), 100);
    int width = 50 + (rand() % 200);
    int height = 50 + (rand() % 100);
    int tile_num = rand() % 4;
    addObstacle(last_x + gap, new_y, width, height, tile_num);
    ObstacleData lastObstacle = *(--obstacles.end());
    last_x = lastObstacle.box.x + lastObstacle.box.w;
    last_y = lastObstacle.box.y;
  }


}

