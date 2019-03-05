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

const int SCREEN_WIDTH = 1026;
const int SCREEN_HEIGHT = 540;
char* WINDOW_NAME = (char *)"platformer";
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
  obstacle_tiles.loadFromFile("images/tiles.png", helper.renderer, 3);
  Obstacles platforms(&obstacle_tiles);

  //Score
  SpriteSheet score_digits;
  score_digits.loadFromFile("images/digits.png", helper.renderer, 10);
  Score score(&score_digits, 5, 2, false, 20, 20, &helper);

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

    //Clear screen
    SDL_SetRenderDrawColor(helper.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(helper.renderer);

    //Render and scroll background
    bg.render(helper.renderer);
    bg.scroll();

    //update and render score
    score.update();
    score.render(helper.renderer);

    //Update and render character
    character.update(&platforms, 10);
    character.render(helper.renderer);
    if (character.isDead()){
      quit = true;
      std::cout << "You died tragically with a total of " << score.getScore() << " points. RIP" << std::endl;
    }

    //Render obstacles
    platforms.generateObstacle(50, 200, 100, helper.getScreenWidth(), helper.getScreenHeight());
    platforms.shift(10, 0);
    platforms.render(helper.renderer);

    //Update screen
    SDL_RenderPresent(helper.renderer);
    SDL_Delay(50);
  }

  //Free resources and close SDL
  helper.~SDLHelper();

	return 0;
}
