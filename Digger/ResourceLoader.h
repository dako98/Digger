#ifndef _RESOURCE_LOADER_
#define _RESOURCE_LOADER_

//IMAGE_STORE

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "Constants.h"



class TextureManager
{
public:
	TextureManager(SDL_Renderer* renderer);

	SDL_Texture* GetTexture(Textures id) const;


	~TextureManager();

private:

	std::array<SDL_Texture*, Textures::COUNT> store;

};


#endif // !_RESOURCE_LOADER_
