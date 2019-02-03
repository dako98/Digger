#include <iostream>
#include "Initialisation.h"
#include "Constants.h"

int main(int argc, char* argv[])
{
	//Create window
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Digger pre-alpha v0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//Initialise renderer
	SDL_SetRenderDrawColor(renderer, MISSING_TEXTURE_COLOR.red, MISSING_TEXTURE_COLOR.green, MISSING_TEXTURE_COLOR.blue, MISSING_TEXTURE_COLOR.opacity);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);



	//Other logic below.




	//test
	TestMakePlayer(renderer);




	return 0;
}