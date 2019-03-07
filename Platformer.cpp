#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "Texture.h"
#include "SDLHelper.h"
#include "SpriteSheet.h"
#include "Obstacles.h"
#include "Background.h"
#include "Character.h"
#include "Score.h"
#include "Coins.h"

const int SCREEN_WIDTH = 1026;
const int SCREEN_HEIGHT = 540;
char* WINDOW_NAME = (char *)"platformer";
const int SCROLL_SPEED = 10;
SDLHelper helper(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME);
//Screen dimension constants

int main() {
  //seed RNG
  srand(time(0));

  //Main loop flag
  bool quit = false;

  //Event handler
  SDL_Event e;

  /*
   * INITIALIZE OBJECTS
   */

  //Background
  Texture bg_texture;
  bg_texture.loadFromFile("images/background.png", helper.renderer);
  Background bg(&bg_texture, 4);

  //Character
  SpriteSheet character_sheet;
  character_sheet.loadFromFile("images/character.png", helper.renderer, 6);
  int charX = bg_texture.getWidth() - 900;
  int charY = bg_texture.getHeight() - 200;
  Character character(&character_sheet, 2, charX, charY);

  //Obstacles
  SpriteSheet obstacle_tiles;
  obstacle_tiles.loadFromFile("images/platforms.png", helper.renderer, 2);
  Obstacles platforms(&obstacle_tiles);

  //Score
  SpriteSheet score_digits;
  score_digits.loadFromFile("images/digits.png", helper.renderer, 10);
  Score score(&score_digits, 5, 2, false, 20, 20, &helper);

  //Coins
  SpriteSheet coin_sprites;
  coin_sprites.loadFromFile("images/coins.png", helper.renderer, 6);
  Coins coins(&coin_sprites, &score, &helper);

  //While application is running, game loop
  while(!quit) {

    //Handle events on queue
    while(SDL_PollEvent(&e) != 0) {
      //User requests quit
      if(e.type == SDL_QUIT) {
        quit = true;
      }
      else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_SPACE:
            if (!character.isJumping()) {
              character.jump();
            }
        }
      }
    }


    //Updates:
    if(!character.isDead()){
      bg.scroll();
      score.update();
      platforms.shift(SCROLL_SPEED, 0);
      coins.handleCollisions(character.getBoundingBox());
      coins.shift(SCROLL_SPEED, 0);
    }
    character.update(&platforms, SCROLL_SPEED);

    //generate coins and obstacles
    platforms.generateObstacle(50, 200, 100, helper.getScreenWidth(), helper.getScreenHeight());
    coins.generateCoin();


    //Renders:
    //Clear screen
    SDL_SetRenderDrawColor(helper.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(helper.renderer);

    bg.render(helper.renderer);
    score.render(helper.renderer);
    character.render(helper.renderer);
    platforms.render(helper.renderer);
    coins.render(helper.renderer);

    SDL_RenderPresent(helper.renderer);
    SDL_Delay(50);

    if (character.isDead() and character.getBoundingBox()->y > helper.getScreenHeight()){
      quit = true;
      std::cout << "You died tragically with a total of " << score.getScore() << " points. RIP" << std::endl;
    }
  }

  //Free resources and close SDL
  helper.~SDLHelper();

	return 0;
}
