#include "Field.h"

Field::Field()
{
	grid.resize(CELLS_IN_COL);
	for (auto &row : grid)
		row.resize(CELLS_IN_ROW);

	for(auto &row:grid)
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

void Field::Print(SDL_Renderer * renderer) const
{

	SDL_Rect cellRect;
	int rowsCount = grid.size();
	int colsCount;
	SDL_Texture* wallTexture;

	for (int row = 0; row < rowsCount; ++row)
	{
		colsCount = grid[row].size();
		for (int col = 0; col < colsCount; ++col)
		{

			cellRect.x = (GAME_FIELD_BEGIN_X + col * CELL_WIDTH);
			cellRect.y = (GAME_FIELD_BEGIN_Y + row * CELL_HEIGHT);
			cellRect.w = CELL_WIDTH;
			cellRect.h = CELL_HEIGHT;

			if (grid[row][col][TOP_WALL])
			{
				SDL_RenderSetViewport(renderer, &cellRect);
				SDL_RenderCopy(renderer, wallTexture, NULL, NULL);
			}
		}
	}
}
