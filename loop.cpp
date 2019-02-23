#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "texture.h"
#include "SDLHelper.h"
#include "animationtest.h"
#include "spriteSheet.h"

SDLHelper helper;

int main()
{
    //Main loop flag
    bool quit = false;
    SpriteSheet blob_sheet;
    blob_sheet.loadFromFile("./blob_sprite.png", helper.renderer, 8);
    AnimationTest blob(&blob_sheet);

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
      blob.render(helper.renderer);
      //Update screen
      SDL_RenderPresent( helper.renderer);
      SDL_Delay(100);

    }


	//Free resources and close SDL
    helper.~SDLHelper();

	return 0;
}
