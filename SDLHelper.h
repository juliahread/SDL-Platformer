#ifndef SDL_HELPER_HEADER
#define SDL_HELPER_HEADER
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class SDLHelper{
public:
  SDLHelper();
  ~SDLHelper();
  bool loadMedia();
  SDL_Window *window;
  SDL_Renderer *renderer;
private:
  bool init();
  void close();
};

#endif
