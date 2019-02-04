#include "Enemy.h"

Enemy::Enemy(int x, int y, Matrix *map)
	:map(map)
	, currentCell(x, y)
	, knowsRoute(false)
{}

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

	int deltaX = 0;
	int deltaY = 0;

	switch (direction)
	{
	case UP:
		deltaY = routeToPlayer.front().y - currentCell.y;
		break;
	case LEFT:
		deltaX = routeToPlayer.front().x - currentCell.x;
		break;
	case DOWN:
		deltaY = routeToPlayer.front().y - currentCell.y;
		break;
	case RIGHT:
		deltaX = routeToPlayer.front().x - currentCell.x;

		break;
	default:
		break;
	}

	entityRect.x = (GAME_FIELD_BEGIN_X + currentCell.x * CELL_WIDTH + deltaX * CELL_WIDTH*(movementProgress / (double)MOVEMENT_STEPS));
	entityRect.y = (GAME_FIELD_BEGIN_Y + currentCell.y * CELL_HEIGHT + deltaY * CELL_HEIGHT*(movementProgress / (double)MOVEMENT_STEPS));
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
			movementProgress = MOVEMENT_STEPS;
		}
		int step = std::min(movementProgress, steps);

		movementProgress -= step;
		steps -= step;
	}
}

coord Enemy::GetCoord() const
{
	return currentCell;
}

bool & Enemy::IsUpToDate()
{
	return knowsRoute;
}

void Enemy::UpdateRoute(std::queue<coord>& newRoute)
{
	routeToPlayer = newRoute;
	knowsRoute = true;
}

Enemy::~Enemy()
{

}
