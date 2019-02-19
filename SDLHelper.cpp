#include "SDLHelper.h"
#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

//Screen dimension constants
const int SCREEN_WIDTH = 700; //TODO: choose screen size
const int SCREEN_HEIGHT = 600;

SDLHelper::SDLHelper(){
  bool initialized = SDLHelper::init();
  if (not initialized){
    throw std::runtime_error( "SDLHelper failed to initialize");
  }
}

SDLHelper::~SDLHelper(){
  SDLHelper::close();
}

bool SDLHelper::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow( "Connect 4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool SDLHelper::loadMedia(Texture spriteSheetTexture)
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if( !spriteSheetTexture.loadFromFile( "gfx/pieces.png", renderer) )
    {
      printf( "Failed to load sprite sheet texture!\n" );
      success = false;
    }
	else
    {
      //Set red piece sprite
      gSpriteClips[ RED ].x =   0;
      gSpriteClips[ RED ].y =   0;
      gSpriteClips[ RED ].w = 100;
      gSpriteClips[ RED ].h = 100;

      //Set yellow piece sprite
      gSpriteClips[ YELLOW ].x = 100;
      gSpriteClips[ YELLOW ].y =   0;
      gSpriteClips[ YELLOW ].w = 100;
      gSpriteClips[ YELLOW ].h = 100;

      //Set empty piece sprite
      gSpriteClips[ EMPTY ].x = 200;
      gSpriteClips[ EMPTY ].y =   0;
      gSpriteClips[ EMPTY ].w = 100;
      gSpriteClips[ EMPTY ].h = 100;
    }

	if( !gWinSpriteSheetTexture.loadFromFile( "gfx/WinTexture.png", gRenderer) ) {
      printf( "Failed to load sprite sheet texture!\n" );
      success = false;
  } else {
    //Set red win sprite
    gWinSpriteClips [ RED ].x = 0;
    gWinSpriteClips [ RED ].y = 0;
    gWinSpriteClips [ RED ].w = 600;
    gWinSpriteClips [ RED ].h = 600;

    //Set yellow win sprite
    gWinSpriteClips [ YELLOW ].x = 600;
    gWinSpriteClips [ YELLOW ].y = 0;
    gWinSpriteClips [ YELLOW ].w = 600;
    gWinSpriteClips [ YELLOW ].h = 600;

    //Set new game sprite
    gWinSpriteClips [ EMPTY ].x = 1800;
    gWinSpriteClips [ EMPTY ].y = 0;
    gWinSpriteClips [ EMPTY ].w = 600;
    gWinSpriteClips [ EMPTY ].h = 600;

    //Set tie sprite
    gWinSpriteClips [ TIE ].x = 1200;
    gWinSpriteClips [ TIE ].y = 0;
    gWinSpriteClips [ TIE ].w = 600;
    gWinSpriteClips [ TIE ].h = 600;
  }

	return success;
}

void SDLHelper::close()
{
	//Free loaded images
	gPieceSpriteSheetTexture.free();
  gWinSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
