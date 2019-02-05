#ifndef _GAME_
#define _GAME_

#include "Field.h"

class Game
{
public:
	Game(SDL_Renderer* renderer);

	void PlayGame();

	~Game();

private:

	Field gameField;

};





#endif // !_GAME_
