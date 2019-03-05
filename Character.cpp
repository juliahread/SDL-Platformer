#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Character.h"
#include "Obstacles.h"

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
  m_dead = false;
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
const SDL_Rect* Character::getBoundingBox() {
  return &m_box;
}

//Update y position of character to animate jump
void Character::update(Obstacles *obstacles, int shift_speed) {
    m_box.y += m_vel;
    std::list <SDL_Rect*> obstacles_hit = obstacles->detectCollisions(&m_box);
    bool on_obstacle = false;
    int obstacle_height;
    for (auto it = obstacles_hit.begin(); it != obstacles_hit.end(); it++){
      SDL_Rect obstacle_hit = *(*it);
      //check if colliding from the top or side
      if ((m_box.y + m_box.h - m_vel) < obstacle_hit.y){
        on_obstacle = true;
        obstacle_height = obstacle_hit.y;
      } else if ((m_box.x + m_box.w - shift_speed) < obstacle_hit.x){
        m_dead = true;
      }
    }


    if (m_box.y > m_ground) {
      m_box.y = m_ground;
      m_jumping = false;
      m_vel = 0;
    } else if(on_obstacle){
      m_box.y = obstacle_height - m_box.h - 1;
      m_jumping = false;
      m_vel = 0;
    } else {
      m_vel += m_acc;
    }
}

//Returns true if character is in jumping state
bool Character::isJumping() {
  return m_jumping;
}

bool Character::isDead(){
  return m_dead;
}
