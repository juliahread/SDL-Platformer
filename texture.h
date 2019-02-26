#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

/*
 * Texture class
 * Wrapper class provided by LazyFoo tutorials
 */
class Texture {
  public:
    //Initializes variables
    Texture();
    //Deallocates memory
    ~Texture();
    //Loads image at specified path
    bool loadFromFile( std::string path, SDL_Renderer* renderer);
    //Deallocates texture
    void free();
    //Renders texture at given point
    void render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL);
    //Gets image dimensions
    int getWidth();
    int getHeight();
  private:
    //The actual hardware texture
    SDL_Texture* m_texture;
    //Image dimensions
    int m_width;
    int m_height;
};

#endif
