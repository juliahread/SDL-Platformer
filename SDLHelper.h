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
    SDLHelper(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, char* WINDOW_NAME);
    ~SDLHelper();
    SDL_Window *window;
    SDL_Renderer *renderer;
    int getScreenWidth();
    int getScreenHeight();
    char *getWindowName();
  private:
    bool init();
    void close();
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    char *WINDOW_NAME;
};

#endif
