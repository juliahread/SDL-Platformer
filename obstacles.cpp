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
  for (int h = 0; h < data.height; h++) {
    for (int w = 0; w < data.length; w++) {
      int screenX = data.x + tileSheet->getWidth() * w;
      int screenY = data.y + tileSheet->getHeight() * h;
      tileSheet->renderSprite(screenX, screenY, renderer, data.tile_num);
    }
  }
}

//Iterates through obstacles and shifts their positions
void Obstacles::shiftObstacles(int xShift, int yShift) {
  std::list <ObstacleData> :: iterator it;
  for (it = obstacles.begin(); it != obstacles.end(); ++it) {
    it->x -= xShift;
    it->y -= yShift;
    if ((it->x + tileSheet->getWidth() * it->length) < 0 or
        (it->y + tileSheet->getHeight() * it->height) < 0) {
      it = obstacles.erase(it);
      it--; //TODO: figure out if this is needed
    }
  }
}

//Adds a new obstacle to the obstacle list
void Obstacles::addObstacle(Obstacles::ObstacleData data) {
  obstacles.push_back(data);
}
