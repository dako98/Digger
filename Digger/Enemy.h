#ifndef _ENEMY_
#define _ENEMY_

#include <queue>
#include <SDL_image.h>

#include "Constants.h"
//#include "Field.h"



class Enemy
{
public:
	Enemy(int x, int y, Matrix *map);

	void Print(SDL_Renderer *renderer, SDL_Texture* texture) const;
	void Advance(int steps);
	coord GetCoord() const;
	bool& IsUpToDate();
	void UpdateRoute(std::queue<coord> &newRoute);

	~Enemy();

private:

	Matrix* map;
	std::queue<coord> routeToPlayer;
	bool knowsRoute;

	coord currentCell;

	int movementProgress;

};



#endif // !_ENEMY_
