#ifndef SDL_HELPER_HEADER
#define SDL_HELPER_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

/*
 * SDLHelper class
 * TODO: describe what this is
 */
class SDLHelper{
  public:
    SDLHelper();
    ~SDLHelper();
    SDL_Window *window;
    SDL_Renderer *renderer;
    int getScreenWidth();
    int getScreenHeight();
  private:
    bool init();
    void close();
};

#endif
