#include <iostream>
#include "Initialisation.h"
#include "Constants.h"
#include "Field.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	//Create window
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Digger alpha v0.7", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//Initialise renderer
	SDL_SetRenderDrawColor(renderer, MISSING_TEXTURE_COLOR.red, MISSING_TEXTURE_COLOR.green, MISSING_TEXTURE_COLOR.blue, MISSING_TEXTURE_COLOR.opacity);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);



	//Other logic below.




	//test
	TestMakePlayer(renderer);

	Game game(renderer);

	game.PlayGame();

//	Field field(renderer);
//	field.Update();
//	field.Print();


	return 0;
}