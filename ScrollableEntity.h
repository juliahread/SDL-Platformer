#ifndef SCROLLABLE_ENTITY_HEADER
#define SCROLLABLE_ENTITY_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>

#include "SpriteSheet.h"

/*
 * Obstacle class
 * Updates positions of and renders list of Obstacles
 */
class ScrollableEntity {
public:
  virtual void render(SDL_Renderer *renderer) = 0;
  virtual void shift(int xShift, int yShift) = 0;
};

#endif
