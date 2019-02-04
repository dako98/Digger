#ifndef _INITIALISATION_
#define _INITIALISATION_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int TestMakePlayer(SDL_Renderer* renderer)
{

	SDL_Texture* player;
	player = IMG_LoadTexture(renderer, "smile.bmp");

	if (player == nullptr)
		std::cerr << "Could not load image.\n";


	SDL_Rect playerRect;

	playerRect.x = 100;
	playerRect.y = 100;
	playerRect.w = 50;
	playerRect.h = 50;



	SDL_RenderSetViewport(renderer, &playerRect);

	SDL_RenderCopy(renderer, player, NULL, NULL);



	SDL_RenderPresent(renderer);


//	SDL_Delay(3'000);

	return 0;
}

#endif // !_INITIALISATION_

