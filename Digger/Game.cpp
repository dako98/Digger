#include "Game.h"

Game::Game(SDL_Renderer* renderer)
	:gameField(renderer)
{

}

void Game::PlayGame()
{

	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	int direction = INVALID_DIRECTION;
	bool playing = true;

	while (playing)
	{

		SDL_PollEvent(&e);
		//User requests playing
		if (e.type == SDL_QUIT)
		{
			playing = false;
		}
		else
		{
			if (keystates[SDL_SCANCODE_UP])
				direction = UP;

			else if (keystates[SDL_SCANCODE_DOWN])
				direction = DOWN;

			else if (keystates[SDL_SCANCODE_LEFT])
				direction = LEFT;

			else if (keystates[SDL_SCANCODE_RIGHT])
				direction = RIGHT;

			bool state = gameField.Update(direction);

			if (state == false)
			{
				std::cout << "game over";
				return;
			}

			if (enemySpawnCooldown <= 0);
			{
				gameField.SpawnEnemy();
				enemySpawnCooldown = ENEMY_SPAWN_COOLDOWN;
			}
			enemySpawnCooldown--;

			direction = INVALID_DIRECTION;
		}

		SDL_Delay(10);
	}
}

Game::~Game()
{

}
