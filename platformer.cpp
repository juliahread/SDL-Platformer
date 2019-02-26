#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Texture.h"
#include "SDLHelper.h"
#include "SpriteSheet.h"
#include "AnimateSprite.h"
#include "Obstacles.h"

SDLHelper helper;

int main() {

  //Main loop flag
  bool quit = false;

  //Event handler
  SDL_Event e;

  /*
   * INITIALIZE OBJECTS
   */

  //Background TODO: finish making class
  Texture bg_texture;
  bg_texture.loadFromFile("images/background.png", helper.renderer);
  int scrollingOffset = 0;

  //Character TODO: finish making class
  SpriteSheet character_sheet;
  character_sheet.loadFromFile("images/character.png", helper.renderer, 6);
  AnimateSprite character(&character_sheet, 2);

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
    }

    //Clear screen
    SDL_SetRenderDrawColor( helper.renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( helper.renderer );

    //Scroll and render background
    scrollingOffset -= 4;
    if (scrollingOffset < -bg_texture.getWidth()) {
      scrollingOffset = 0;
    }
    bg_texture.render(scrollingOffset, 0, helper.renderer);
    bg_texture.render(scrollingOffset + bg_texture.getWidth(), 0, helper.renderer);

    //Render character
    character.render(bg_texture.getWidth() - 900, bg_texture.getHeight() - 200, helper.renderer);

    //Render objects
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
