#ifndef _PLAYER_
#define _PLAYER_

#include <SDL_image.h>

#include "Constants.h"

class Player
{
public:
	Player(coord start);

	void Print(SDL_Renderer *renderer, SDL_Texture* texture) const;


	bool Die();

	void AddScore(int score);
	void AddAmmo();
	coord GetCoord() const;
	coord DrawingCoord() const;
	void AlignedMove(int direction);

	void Move(int direction);
	int getClosestDir();

	~Player();

private:

	int lives;
	int score;
	int ammo;

//	int movementProgress;

	int facing;

	coord currentCell;
	coord drawingCoordinates;
};




#endif // !_PLAYER_
