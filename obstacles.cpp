#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "obstacles.h"
#include <list>
#include <iterator>
#include <iostream>

Obstacles::Obstacles(SpriteSheet *tileSheetArg){
  tileSheet = tileSheetArg;
  std::list <ObstacleData> obstacles;
}

Obstacles::~Obstacles(){
}

void Obstacles::render(SDL_Renderer *renderer){
  std::list <ObstacleData> :: iterator it;
  for (it = obstacles.begin(); it != obstacles.end(); ++it){
    renderObstacle(*it, renderer);
  }
  std::cout << obstacles.size() << std::endl << std::flush;
}

void Obstacles::renderObstacle(ObstacleData data, SDL_Renderer *renderer){
  for (int h = 0; h < data.height; h++){
    for (int w = 0; w < data.length; w++){
      int screenX = data.x + tileSheet->getWidth() * w;
      int screenY = data.y + tileSheet->getHeight() * h;
      tileSheet->renderSprite(screenX, screenY, renderer, data.tile_num);
    }
  }
}

void Obstacles::shiftObstacles(int xShift, int yShift){
  std::list <ObstacleData> :: iterator it;
  for (it = obstacles.begin(); it != obstacles.end(); ++it){
    it->x -= xShift;
    it->y -= yShift;
    if ((it->x + tileSheet->getWidth() * it->length) < 0 or (it->y + tileSheet->getHeight() * it->height) < 0){
      it = obstacles.erase(it);
      it--; //TODO: figure out if this is needed
    }
  }
}

void Obstacles::addObstacle(Obstacles::ObstacleData data){
  obstacles.push_back(data);
}
