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
char* WINDOW_NAME = "platformer";
SDLHelper helper(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME);
//Screen dimension constants

int main() {

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
  obstacle_tiles.loadFromFile("images/tiles.png", helper.renderer, 4);
  Obstacles platforms(&obstacle_tiles);
  int frame_num = 0;
  srand(0);

  //Score
  SpriteSheet score_digits;
  score_digits.loadFromFile("images/digits.png", helper.renderer, 10);
  // Score score(&score_digits, helper, 5, 2, 20, 20);
  std::cout << "made score" << std::endl << std::flush;

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
            character.jump();
        }
      }
    }

    //Clear screen
    SDL_SetRenderDrawColor(helper.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(helper.renderer);

    //Render and scroll background
    bg.render(helper.renderer);
    bg.scroll();

    //Render character
    character.render(helper.renderer);

    //update and render score
    // score.update();
    // score.render(helper.renderer);

    //Render obstacles
    frame_num++;
    if (not (frame_num % 75)){
      Obstacles::ObstacleData newPlatform;
      newPlatform.box.x = helper.getScreenWidth();
      newPlatform.box.y = rand() % helper.getScreenHeight();
      newPlatform.box.h = 50 + (rand() % 100);
      newPlatform.box.w = 50 + (rand() % 200);
      newPlatform.tile_num = rand() % 4;
      platforms.addObstacle(newPlatform);
    }
    platforms.shiftObstacles(3, 0);
    SDL_Rect test;
    test.x = 100;
    test.y = 100;
    test.w = 100;
    test.h = 100;
    platforms.detectCollisions(&test);
    platforms.render(helper.renderer);

    //Update screen
    SDL_RenderPresent(helper.renderer);
    SDL_Delay(50);

  }

  //Free resources and close SDL
  helper.~SDLHelper();

	return 0;
}
