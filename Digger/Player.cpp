#include "Player.h"

void Player::Print(SDL_Renderer * renderer, SDL_Texture* texture) const
{
	{
		SDL_Rect entityRect;
		int direction = 0;

		/*
		if (currentCell.y > routeToPlayer.front().y)
			direction = UP;

		else if (currentCell.x > routeToPlayer.front().x)
			direction = LEFT;

		else if (currentCell.y < routeToPlayer.front().y)
			direction = DOWN;

		else if (currentCell.x < routeToPlayer.front().x)
			direction = RIGHT;
			*/

		int deltaX = 0;
		int deltaY = 0;


//		deltaY = routeToPlayer.front().y - currentCell.y;

//		deltaX = routeToPlayer.front().x - currentCell.x;


//		entityRect.x = (GAME_FIELD_BEGIN_X + currentCell.x * CELL_WIDTH + deltaX * CELL_WIDTH*(movementProgress / (double)MOVEMENT_STEPS));
//		entityRect.y = (GAME_FIELD_BEGIN_Y + currentCell.y * CELL_HEIGHT + deltaY * CELL_HEIGHT*(movementProgress / (double)MOVEMENT_STEPS));

		entityRect.x = drawingCoordinates.x;
		entityRect.y = drawingCoordinates.y;

		entityRect.w = PLAYER_WIDTH;
		entityRect.h = PLAYER_HEIGHT;

		SDL_RenderSetViewport(renderer, &entityRect);
		SDL_RenderCopyEx(renderer, texture, NULL, NULL, 90 * direction, NULL, SDL_RendererFlip(SDL_FLIP_NONE));
	}
}

Player::Player(coord start)
	:currentCell(start)
//	, movementProgress(0)
	, lives(PLAYER_LIVES)
	,facing(INVALID_DIRECTION)
{
	drawingCoordinates.x = currentCell.x*CELL_WIDTH;
	drawingCoordinates.y = currentCell.y*CELL_HEIGHT;

}

bool Player::Die()
{
	return --lives > 0;
}

void Player::AddScore(int score)
{
	this->score += score;
}

void Player::AddAmmo()
{
	ammo++;
}

coord Player::GetCoord() const
{
	return coord((drawingCoordinates.x + PLAYER_WIDTH / 2) / CELL_WIDTH,
		(drawingCoordinates.y + PLAYER_HEIGHT / 2) / CELL_HEIGHT);
}

coord Player::DrawingCoord() const
{
	return drawingCoordinates;
}

void Player::Move(int direction)
{
	switch (direction)
	{
	case UP:
		if (drawingCoordinates.y - PLAYER_STEP >= 0)
		{
			drawingCoordinates.y -= PLAYER_STEP;
		}
		break;
	case LEFT:
		if (drawingCoordinates.x - PLAYER_STEP >= 0)
		{
			drawingCoordinates.x -= PLAYER_STEP;
		}
		break;
	case DOWN:
		if (drawingCoordinates.y + PLAYER_STEP <= CELLS_IN_COL * CELL_HEIGHT - PLAYER_HEIGHT)
		{
			drawingCoordinates.y += PLAYER_STEP;
		}
		break;
	case RIGHT:
		if (drawingCoordinates.x + PLAYER_STEP <= CELLS_IN_ROW * CELL_WIDTH - PLAYER_WIDTH)
		{
			drawingCoordinates.x += PLAYER_STEP;
		}
		break;
	default:
		//nothing
		break;
	}




	






/*
	if ((pos.x >= STEP && _move.X < 0) || (pos.x < SCREEN_WIDTH - width() && _move.X > 0))
		pos.x += _move.X * STEP;

	if ((pos.y >= STEP && _move.Y < 0) || (pos.y < SCREEN_HEIGHT - height() && _move.Y > 0))
		pos.y += _move.Y * STEP;

	lastMove = _move;

	if (_move.X || _move.Y)
		lastActiveMove = _move;
		*/
}

Player::~Player()
{

}



void Player::AlignedMove(int direction)
{
	// if we are at the center of a block
	if ((drawingCoordinates.x % CELL_WIDTH == (CELL_WIDTH - PLAYER_WIDTH) / 2)
		&& (drawingCoordinates.y % CELL_HEIGHT == (CELL_HEIGHT - PLAYER_HEIGHT) / 2))
	{
		Move(direction);
	}
	else
	{
		// if our last move was on x axis
		// and we want to change the direction
		if ((facing == LEFT || facing == RIGHT)
			&& (direction == LEFT || direction == RIGHT))
		{
			Move(direction);
		}
		// if our last move was on y axis
		// and we want to change the direction
		else if ((facing == UP || facing == DOWN)
			&& (direction == UP || direction == DOWN))
		{
			Move(direction);
		}

		else if (direction !=INVALID_DIRECTION)
		{ // keep the same direction
			Move(getClosestDir());
//			return false;
		}
	}
	facing = direction;
}

void Player::Respawn()
{
	currentCell = PLAYER_SPAWN;
	facing = INVALID_DIRECTION;

	drawingCoordinates.x = currentCell.x*CELL_WIDTH;
	drawingCoordinates.y = currentCell.y*CELL_HEIGHT;
}


int Player::getClosestDir()
{
	if (facing == UP || facing == DOWN)
	{
		if (drawingCoordinates.y + PLAYER_HEIGHT / 2 % CELL_HEIGHT >= CELL_HEIGHT / 2)
			return UP;
		else
			return DOWN;
	}
	else
	{
		if (drawingCoordinates.x + PLAYER_WIDTH / 2 % CELL_HEIGHT >= CELL_HEIGHT / 2)
			return LEFT;
		else
			return RIGHT;
	}
	return INVALID_DIRECTION;
}