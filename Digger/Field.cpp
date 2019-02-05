#include "Field.h"
#include "Algorithms.h"

Field::Field(SDL_Renderer* renderer)
	:textures(renderer)
	, player(PLAYER_SPAWN)
	, renderer(renderer)
{
	grid.resize(CELLS_IN_COL);
	for (auto &row : grid)
		row.resize(CELLS_IN_ROW);

	for (auto &row : grid)
	{
		for (auto &cell : row)
		{
			cell[TOP_WALL] = 1;
			cell[LEFT_WALL] = 1;
			cell[RIGHT_WALL] = 1;
			cell[BOTTOM_WALL] = 1;

			cell[DIFFICULTY - 1] = 0;
			cell[DIFFICULTY] = 0;
			cell[GEM] = 0;
			cell[BAG] = 0;
		}
	}

	RandomDFS(grid, INITIAL_MAZE_LENGTH,PLAYER_SPAWN);
	monsterSpawner = FarthestCell(grid, PLAYER_SPAWN);

	enemies.push_back(Enemy(monsterSpawner, &grid));
	previousPlayerPos = coord(-1, -1);
}

void Field::Print() const
{

	int rowsCount = grid.size();
	int colsCount;



	SDL_Texture* texture = textures.GetTexture(Textures::MISSING_TEXTURE);

	for (int row = 0; row < rowsCount; ++row)
	{
		colsCount = grid[row].size();
		for (int col = 0; col < colsCount; ++col)
		{
			if (grid[row][col]==0b11110000)	//full cell
			{
				SDL_Rect cellRect;
				texture = textures.GetTexture(Textures::NORMAL_DIRT_TEXTURE);

				cellRect.x = (GAME_FIELD_BEGIN_X + col * CELL_WIDTH);
				cellRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT);
				cellRect.w = CELL_WIDTH;
				cellRect.h = CELL_HEIGHT;

				SDL_RenderSetViewport(renderer, &cellRect);
				SDL_RenderCopy(renderer, texture, NULL, NULL);

				continue;
			}
			else
			{
				SDL_Rect cellRect;
				texture = textures.GetTexture(Textures::NO_DIRT_TEXTURE);

				cellRect.x = (GAME_FIELD_BEGIN_X + col * CELL_WIDTH);
				cellRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT);
				cellRect.w = CELL_WIDTH;
				cellRect.h = CELL_HEIGHT;

				SDL_RenderSetViewport(renderer, &cellRect);
				SDL_RenderCopy(renderer, texture, NULL, NULL);
			}
			SDL_Rect wallRect;

			texture = textures.GetTexture(Textures::WALL_TEXTURE);

			if (grid[row][col][TOP_WALL])
			{
				wallRect.x = (GAME_FIELD_BEGIN_X + col * CELL_WIDTH);
				wallRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT);
				wallRect.w = WALL_WIDTH;
				wallRect.h = WALL_HEIGTH;

				SDL_RenderSetViewport(renderer, &wallRect);
				//SDL_RenderCopy(renderer, texture, NULL, NULL);
				SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_RendererFlip(SDL_FLIP_NONE));

			}

			if (grid[row][col][LEFT_WALL])
			{ /*
				wallRect.x = (GAME_FIELD_BEGIN_X + col * CELL_WIDTH);
				wallRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT);
				wallRect.w = VERTICAL_WALL_WIDTH;
				wallRect.h = VERTICAL_WALL_HEIGTH;
				*/
				wallRect.x = (GAME_FIELD_BEGIN_X + col * CELL_WIDTH);
				wallRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT);
				wallRect.w = WALL_HEIGTH;
				wallRect.h = WALL_WIDTH;

				SDL_RenderSetViewport(renderer, &wallRect);
				//SDL_RenderCopy(renderer, texture, NULL, NULL);
				SDL_RenderCopyEx(renderer, texture, NULL, NULL, 90, NULL, SDL_RendererFlip(SDL_FLIP_NONE));
			}

			if (grid[row][col][BOTTOM_WALL])
			{
				wallRect.x = (GAME_FIELD_BEGIN_X + col * CELL_WIDTH);
				wallRect.y = (GAME_FIELD_BEGIN_Y + (row + 1) * CELL_HEIGHT - WALL_HEIGTH);
				wallRect.w = WALL_WIDTH;
				wallRect.h = WALL_HEIGTH;

				SDL_RenderSetViewport(renderer, &wallRect);
				SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_RendererFlip(SDL_FLIP_NONE));
			}

			if (grid[row][col][RIGHT_WALL])
			{
//				wallRect.x = (GAME_FIELD_BEGIN_X + (col+1) * CELL_WIDTH - VERTICAL_WALL_WIDTH);
//				wallRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT);
//				wallRect.h = VERTICAL_WALL_WIDTH;
//				wallRect.w = VERTICAL_WALL_HEIGTH;
//
//				SDL_RenderSetViewport(renderer, &wallRect);
//				SDL_RenderCopyEx(renderer, texture, NULL, NULL, 90, NULL, SDL_RendererFlip(SDL_FLIP_NONE));
			}



		}
	}

	SDL_Rect cellRect;
	texture = textures.GetTexture(Textures::SPAWNER_TEXTURE);

	cellRect.x = (GAME_FIELD_BEGIN_X + monsterSpawner.x * CELL_WIDTH + WALL_HEIGTH);
	cellRect.y = (GAME_FIELD_BEGIN_Y + monsterSpawner.y * CELL_HEIGHT + WALL_HEIGTH);
	cellRect.w = CELL_WIDTH - 2* WALL_HEIGTH;
	cellRect.h = CELL_HEIGHT - 2* WALL_HEIGTH;

	SDL_RenderSetViewport(renderer, &cellRect);
	SDL_RenderCopy(renderer, texture, NULL, NULL);

//	SDL_RenderPresent(renderer);

	for (const auto& enemy : enemies)
		enemy.Print(renderer, textures.GetTexture(Textures::ENEMY_TEXTURE));

	player.Print(renderer, textures.GetTexture(Textures::PLAYER_TEXTURE));

}

void Field::Update(int direction)
{

	player.AlignedMove(direction);

	//	Print();

	if (previousPlayerPos != player.GetCoord())
	{

		switch (direction)
		{
		case UP:
//			if (player.GetCoord().y >= 0)
			{
				ConnectCells(grid, player.GetCoord(), previousPlayerPos);
			}
			break;

		case LEFT:
			ConnectCells(grid, player.GetCoord(), previousPlayerPos/*coord(player.GetCoord().x - 1, player.GetCoord().y)*/);

			break;
		case DOWN:
			ConnectCells(grid, player.GetCoord(), previousPlayerPos/*coord(player.GetCoord().x, player.GetCoord().y + 1)*/);

			break;
		case RIGHT:
			ConnectCells(grid, player.GetCoord(), previousPlayerPos/*coord(player.GetCoord().x + 1, player.GetCoord().y)*/);

			break;
		case INVALID_DIRECTION:
			break;
		default:
			break;
		}
	}

	if (previousPlayerPos != player.GetCoord())
	{

	std::cout << "Player current cell: x=" << player.GetCoord().x << " y=" << player.GetCoord().y << '\n';
	std::cout << "Player previous cell: x=" << previousPlayerPos.x << " y=" << previousPlayerPos.y << '\n';
		
	previousPlayerPos = player.GetCoord();

		for (auto &enemy : enemies)
			enemy.IsUpToDate() = false;

		ConstructPaths(grid, player.GetCoord(), enemies);
	}


	for (auto &enemy : enemies)
		enemy.Advance(ENEMY_STEP);

	Print();

	SDL_RenderPresent(renderer);

}



Field::~Field()
{

}
