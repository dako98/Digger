#include "ResourceLoader.h"

TextureManager::TextureManager(SDL_Renderer* renderer)
{
	//Just in case.
	for (size_t i = 0; i < Textures::COUNT; i++)
	{
		store[i] = nullptr;
	}

	for (size_t i = 0; i < Textures::COUNT; i++)
	{
		store[i]= IMG_LoadTexture(renderer, TEXTURE_PATHS[i]);

		if (store[i] == nullptr)
		{
			std::cerr<<"Could not load image \"" << TEXTURE_PATHS[i] << "\". Using \""<<
				TEXTURE_PATHS[MISSING_TEXTURE] <<"\" instead.\n";
			store[i] = store[MISSING_TEXTURE];

			if (store[i]==nullptr)
			{
				std::cerr << "Could not load image \"" << TEXTURE_PATHS[MISSING_TEXTURE] 
					<< "\". Using missing texture colour instead.\n";
			}
		}
	}
}

SDL_Texture * TextureManager::GetTexture(Textures id) const
{
	return store[id];
}

TextureManager::~TextureManager()
{

}
