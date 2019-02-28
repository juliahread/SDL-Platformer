#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Character.h"

//Character constructor takes in SpriteSheet
Character::Character(SpriteSheet* char_sheet, int speed, int x, int y) {
  m_char_sheet = char_sheet;
  m_speed = speed;
  m_ground = y;
  m_frame_number = 0;
  m_iteration = 0;
  m_box.x = x;
  m_box.y = y;
  m_box.w = char_sheet->getWidth();
  m_box.h = char_sheet->getHeight();
  m_jumping = false;
  m_acc = 4;
  m_vel = 0;
}

//Character destructor, nothing to do because everything is on the heap
Character::~Character() {}

//Renders correct Character sprite at its position
void Character::render(SDL_Renderer *renderer) {
  if (m_iteration == m_speed) {
    m_char_sheet->renderSprite(m_box.x, m_box.y, renderer, m_frame_number++);
    m_iteration = 0;
  }
  else {
    m_char_sheet->renderSprite(m_box.x, m_box.y, renderer, m_frame_number);
  }
  if (!m_jumping) {
    m_iteration++;
  }
}

//Character is in jumping state
void Character::jump() {
  m_jumping = true;
  m_vel = -40;
}

//Returns bounding box of sprite
SDL_Rect Character::getBoundingBox() {
  return m_box;
}

//Update y position of character to animate jump
void Character::updateY() {
  if (m_jumping) {
    m_vel += m_acc;
    m_box.y += m_vel;

    if (m_box.y >= m_ground) {
      m_box.y = m_ground;
      m_jumping = false;
      m_vel = 0;
    }
  }
}

//Returns true if character is in jumping state
bool Character::isJumping() {
  return m_jumping;
}
