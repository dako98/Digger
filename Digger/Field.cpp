#include "Field.h"
#include "Algorithms.h"


void PopulateGems(Matrix &map);

Field::Field(SDL_Renderer* renderer)
	:textures(renderer)
	, player(PLAYER_SPAWN)
	, renderer(renderer)
	, gems(GEMS_COUNT)
{
#ifndef DEBUG

	srand(time(0));

#endif // !DEBUG


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

	RandomDFS(grid, INITIAL_MAZE_LENGTH, PLAYER_SPAWN);

	PopulateGems(grid);

	monsterSpawner = FarthestCell(grid, PLAYER_SPAWN);

	previousPlayerPos = coord(-1, -1);
}

void PopulateGems(Matrix &map)
{
	int x, y, usedGems = 0;

	while (usedGems<GEMS_COUNT)
	{
		x = rand() % CELLS_IN_ROW;
		y = rand() % CELLS_IN_COL;

		if (map[y][x] == 0b11110000)
		{
			map[y][x][GEM] = 1;
			usedGems++;
		}
	}
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
			if (grid[row][col].to_ulong() >=  0b11110000)	//full cell
			{
				SDL_Rect cellRect;
				texture = textures.GetTexture(Textures::NORMAL_DIRT_TEXTURE);

				cellRect.x = (GAME_FIELD_BEGIN_X + col * CELL_WIDTH);
				cellRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT);
				cellRect.w = CELL_WIDTH;
				cellRect.h = CELL_HEIGHT;


				SDL_RenderSetViewport(renderer, &cellRect);
				SDL_RenderCopy(renderer, texture, NULL, NULL);

				if (grid[row][col][GEM] == 1)
				{
					SDL_Rect cellRect;
					texture = textures.GetTexture(Textures::GEM_TEXTURE);

					cellRect.x = (GAME_FIELD_BEGIN_X + col * CELL_WIDTH + CELL_WIDTH / 2 - ITEM_WIDTH / 2);
					cellRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT + CELL_HEIGHT / 2 - ITEM_HEIGHT / 2);
					cellRect.w = ITEM_WIDTH;
					cellRect.h = ITEM_HEIGHT;


					SDL_RenderSetViewport(renderer, &cellRect);
					SDL_RenderCopy(renderer, texture, NULL, NULL);
				}

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
				SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_RendererFlip(SDL_FLIP_NONE));
			}

			if (grid[row][col][LEFT_WALL])
			{
				wallRect.x = (GAME_FIELD_BEGIN_X + col * CELL_WIDTH - CELL_WIDTH / 2 + WALL_HEIGTH / 2 + WALL_HEIGTH*2);
				wallRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT);
				wallRect.w = WALL_HEIGTH;
				wallRect.h = WALL_WIDTH;

				SDL_RenderSetViewport(renderer, &wallRect);
				SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_RendererFlip(SDL_FLIP_NONE));
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

				wallRect.x = (GAME_FIELD_BEGIN_X + (col + 1)* CELL_WIDTH - CELL_WIDTH / 2 + WALL_WIDTH / 2 - WALL_HEIGTH);
				wallRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT);
				wallRect.w = WALL_HEIGTH;
				wallRect.h = WALL_WIDTH;

				SDL_RenderSetViewport(renderer, &wallRect);
				SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_RendererFlip(SDL_FLIP_NONE));
//				SDL_RenderCopyEx(renderer, texture, &tmp, &wallRect, 90, NULL, SDL_RendererFlip(SDL_FLIP_NONE));

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

	for (const auto& enemy : enemies)
		enemy.Print(renderer, textures.GetTexture(Textures::ENEMY_TEXTURE));



	player.Print(renderer, textures.GetTexture(Textures::PLAYER_TEXTURE));

}

bool Field::Update(int direction)
{
	if (gems == 0)
	{
		return false;
	}

	player.AlignedMove(direction);

	coord currentPosition = player.GetCoord();

	if (previousPlayerPos != player.GetCoord())
	{

		switch (direction)
		{
		case UP:
			ConnectCells(grid, player.GetCoord(), previousPlayerPos);
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



		if (grid[currentPosition.y][currentPosition.x][GEM] == 1)
		{
			player.AddScore(GEM_SCORE);
			grid[currentPosition.y][currentPosition.x][GEM] == 0;
			gems--;
		}

	}

	for (const auto &enemy : enemies)
	{
		if (enemy.GetCoord() == currentPosition)
		{
			if (player.Die() == false)
			{
//				break;
				return false;
			}
			else
			{
				Reset();
			}
		}
	}

	if (previousPlayerPos != player.GetCoord())
	{

#ifdef DEBUG

	std::cout << "Player current cell: x=" << player.GetCoord().x << " y=" << player.GetCoord().y << '\n';
	std::cout << "Player previous cell: x=" << previousPlayerPos.x << " y=" << previousPlayerPos.y << '\n';

#endif // !DEBUG

	previousPlayerPos = player.GetCoord();

		for (auto &enemy : enemies)
			enemy.IsUpToDate() = false;

		ConstructPaths(grid, player.GetCoord(), enemies);
	}


	for (auto &enemy : enemies)
		enemy.Advance(ENEMY_STEP);

	Print();

	SDL_RenderPresent(renderer);


	return true;
}

void Field::Reset()
{
	enemies.erase(enemies.begin(), enemies.end());
	player.Respawn();
}

void Field::SpawnEnemy()
{
	if (enemies.size() <= MAX_ENEMIES_COUNT)
	{
		enemies.push_back(Enemy(monsterSpawner, &grid));
		enemies.back().IsUpToDate() = false;
		ConstructPaths(grid, player.GetCoord(), enemies);
	}
}



Field::~Field()
{

}
