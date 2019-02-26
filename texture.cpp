#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Texture.h"

//Constructor initializes variables
Texture::Texture() {
	m_texture = NULL;
	m_width = 0;
	m_height = 0;
}

//Destructor deallocates memory
Texture::~Texture() {
	free();
}

//Creates Texture object from a file given file path
bool Texture::loadFromFile( std::string path, SDL_Renderer* renderer) {
	//Get rid of preexisting texture
	free();
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		//Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			//Get image dimensions
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_texture = newTexture;
	return m_texture != NULL;
}

//Frees texture if it exists
void Texture::free() {
	if (m_texture != NULL) {
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}

//Renders texture to the screen
void Texture::render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, m_width, m_height};

	//Set clip rendering dimensions
	if(clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(renderer, m_texture, clip, &renderQuad);
}

int Texture::getWidth() {
	return m_width;
}

int Texture::getHeight() {
	return m_height;
}
