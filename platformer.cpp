#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "texture.h"
#include "SDLHelper.h"
#include "spriteSheet.h"
#include "obstacles.h"

SDLHelper helper;

int main()
{
    //Main loop flag
    bool quit = false;
    SpriteSheet obstacle_tiles;
    obstacle_tiles.loadFromFile("./tiles.png", helper.renderer, 4);
    Obstacles platforms(&obstacle_tiles);
    int frame_num = 0;
    srand(0);

    //Event handler
    SDL_Event e;

    //While application is running, game loop
    while( !quit )
    {
      //Handle events on queue
      while( SDL_PollEvent( &e ) != 0 )
      {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
          quit = true;
        }

      }

      //Clear screen
      SDL_SetRenderDrawColor( helper.renderer, 0x00, 0x00, 0xFF, 0xFF );
      SDL_RenderClear( helper.renderer);

      //Render objects
      frame_num++;
      if (not (frame_num % 75)){
        Obstacles::ObstacleData newPlatform;
        newPlatform.x = 700;
        newPlatform.y = rand() % 600;
        newPlatform.height = 1;
        newPlatform.length = 3;
        newPlatform.tile_num = rand() % 4;
        platforms.addObstacle(newPlatform);
      }
      platforms.shiftObstacles(3, 0);
      platforms.render(helper.renderer);
      //Update screen
      SDL_RenderPresent( helper.renderer);
      SDL_Delay(50);

    }


	//Free resources and close SDL
    helper.~SDLHelper();

	return 0;
}
