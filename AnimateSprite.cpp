#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "spriteSheet.h"
#include "AnimateSprite.h"

//AnimateSprite constructor takes in a SpriteSheet and speed
//Initializes frame num and iteration to 0
AnimateSprite::AnimateSprite(SpriteSheet* sheet, int speed) {
  m_sheet = sheet;
  m_frame_number = 0;
  m_iteration = 0;
  m_speed = speed;
}

//AnimateSprite destructor
AnimateSprite::~AnimateSprite() {
  //fill in destructor?
}

//Renders correct frame of sprite at a given position
void AnimateSprite::render(int x, int y, SDL_Renderer *renderer) {
  if (m_iteration == m_speed) {
    m_sheet->renderSprite(x, y, renderer, m_frame_number++);
    m_iteration = 0;
  }
  else {
    m_sheet->renderSprite(x, y, renderer, m_frame_number);
  }
  m_iteration++;
}
