#include "Enemy.h"

Enemy::Enemy(int x, int y, Matrix * map)
	:map(map)
	, currentCell(x, y)
{
}

void Enemy::Print(SDL_Renderer *renderer, SDL_Texture* texture) const
{
	SDL_Rect entityRect;
	int direction;


	if (currentCell.y > routeToPlayer.front().y)
		direction = UP;

	else if (currentCell.x > routeToPlayer.front().x)
		direction = LEFT;

	else if (currentCell.y < routeToPlayer.front().y)
		direction = DOWN;

	else if (currentCell.x < routeToPlayer.front().x)
		direction = RIGHT;


	entityRect.x = (GAME_FIELD_BEGIN_X + currentCell.x * CELL_WIDTH);
	entityRect.y = (GAME_FIELD_BEGIN_Y + currentCell.y * CELL_HEIGHT);
	entityRect.w = CELL_WIDTH;
	entityRect.h = CELL_HEIGHT;

	SDL_RenderSetViewport(renderer, &entityRect);
	SDL_RenderCopyEx(renderer, texture, NULL, NULL, 90*direction, NULL, SDL_RendererFlip(SDL_FLIP_NONE));
}

void Enemy::Advance(int steps)
{
	while (steps > 0 && !routeToPlayer.empty())
	{
		if (movementProgress == 0)
		{
			currentCell = routeToPlayer.front();
			routeToPlayer.pop();
		}
		int step = std::min(movementProgress, steps);

		movementProgress -= step;
		steps -= step;
	}
}
