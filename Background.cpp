#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Background.h"

//Background constructor takes in texture and speed
Background::Background(Texture* bg_texture, int speed) {
  m_bg_texture = bg_texture;
  m_speed = speed;
  m_y = 0;
  m_scrolling_offset = 0;
}

//Background destructor, nothing to do because everything is on the heap
Background::~Background() {}

//Renders background at correct position
void Background::render(SDL_Renderer *renderer) {
  int x1 = m_scrolling_offset;
  int x2 = m_scrolling_offset + m_bg_texture->getWidth();
  m_bg_texture->render(x1, m_y, renderer);
  m_bg_texture->render(x2, m_y, renderer);
}

//Scrolls at its speed
void Background::scroll() {
  m_scrolling_offset -= m_speed;
  if (m_scrolling_offset < -m_bg_texture->getWidth()) {
    m_scrolling_offset = 0;
  }
}
