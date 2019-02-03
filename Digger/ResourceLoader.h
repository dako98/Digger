#ifndef _RESOURCE_LOADER_
#define _RESOURCE_LOADER_

//IMAGE_STORE

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>


void LoadImage(SDL_Renderer* renderer, std::vector<SDL_Texture*> &store,
				std::string &path, int ID)
{
	if (store[ID] == nullptr)
	{

		store[ID] = IMG_LoadTexture(renderer, path.c_str());

		if (store[ID] == nullptr)
			std::cerr << "Could not load image \"" << path << "\".\n";
		return;
	}
}




#endif // !_RESOURCE_LOADER_
