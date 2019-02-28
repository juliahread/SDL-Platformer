#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Texture.h"
#include "SDLHelper.h"
#include "SpriteSheet.h"
#include "Obstacles.h"
#include "Background.h"
#include "Character.h"

SDLHelper helper;

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

    //Update and render character
    character.updateY();
    character.render(helper.renderer);

    //Render obstacles
    frame_num++;
    if (not (frame_num % 75)){
      Obstacles::ObstacleData newPlatform;
      newPlatform.x = helper.getScreenWidth();
      newPlatform.y = rand() % helper.getScreenHeight();
      newPlatform.height = 1;
      newPlatform.length = 3;
      newPlatform.tile_num = rand() % 4;
      platforms.addObstacle(newPlatform);
    }
    platforms.shiftObstacles(3, 0);
    platforms.render(helper.renderer);

    //Update screen
    SDL_RenderPresent(helper.renderer);
    SDL_Delay(50);

  }

  //Free resources and close SDL
  helper.~SDLHelper();

	return 0;
}
