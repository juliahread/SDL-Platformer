#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "obstacles.h"
#include <list>
#include <iterator>

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
