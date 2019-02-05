#include "Algorithms.h"


void RandomDFS(Matrix &map, int debth, coord begin)
{
	bool done = false;
	_RandomDFS(map, debth, begin.x, begin.y, done);
}

void ConnectCells(Matrix &map, coord cell1, coord cell2)
{
	if (cell1.x < 0 || cell1.x >= CELLS_IN_ROW || cell1.y < 0 || cell1.y >= CELLS_IN_COL ||
		cell2.x < 0 || cell2.x >= CELLS_IN_ROW || cell2.y < 0 || cell2.y >= CELLS_IN_COL)
	{
		return;
	}

	if (cell1.x == cell2.x)
	{
		map[std::min(cell1.y, cell2.y)][cell1.x][CellData::BOTTOM_WALL] = 0;
		map[std::max(cell1.y, cell2.y)][cell1.x][CellData::TOP_WALL] = 0;
		return;
	}

	if (cell1.y == cell2.y)
	{
		map[cell1.y][std::min(cell1.x, cell2.x)][CellData::RIGHT_WALL] = 0;
		map[cell1.y][std::max(cell1.x, cell2.x)][CellData::LEFT_WALL] = 0;
		return;
	}
}

void GetUnvisitedNeighbours(Matrix &map, std::vector<coord> &neightbours, int x, int y)
{
	neightbours.erase(neightbours.begin(), neightbours.end());
	//get all unvisited neighbours
	if (x > 0 && map[y][x - 1] == 0b11110000)
		neightbours.push_back(coord(x - 1, y));

	if (x + 1 < map[y].size() && map[y][x + 1] == 0b11110000)
		neightbours.push_back(coord(x + 1, y));

	if (y > 0 && map[y - 1][x] == 0b11110000)
		neightbours.push_back(coord(x, y - 1));

	if (y + 1 < map.size() && map[y + 1][x] == 0b11110000)
		neightbours.push_back(coord(x, y + 1));
}

void GetNeighbours(const Matrix & map, std::vector<coord>& neightbours, int x, int y)
{
	neightbours.erase(neightbours.begin(), neightbours.end());

	//get all neighbours
	if (map[y][x][LEFT_WALL] == 0)
		neightbours.push_back(coord(x - 1, y));

	if (map[y][x][RIGHT_WALL] == 0)
		neightbours.push_back(coord(x + 1, y));

	if (map[y][x][TOP_WALL] == 0)
		neightbours.push_back(coord(x, y - 1));

	if (map[y][x][BOTTOM_WALL] == 0)
		neightbours.push_back(coord(x, y + 1));
}

void _RandomDFS(Matrix &map, int debth, int x, int y, bool &done)
{
	if (debth <= 0)
	{
		done = true;
		return;
	}

	if (!done)
	{
		std::vector<coord> neightbours;

		GetUnvisitedNeighbours(map, neightbours, x, y);


		//if if got stuck, it will choose a new path
		while (neightbours.size() > 0 && !done)
		{
			int direction = rand() % neightbours.size();

			ConnectCells(map, coord(x, y), neightbours[direction]);

			_RandomDFS(map, debth - 1, neightbours[direction].x, neightbours[direction].y, done);
			GetUnvisitedNeighbours(map, neightbours, x, y);
		}
	}
}

coord FarthestCell(Matrix &map, coord begin)
{
	std::unordered_set <coord> used;

	std::queue<coord> que;

	que.push(begin);

	coord current(begin);
	std::vector<coord> neighbours;

	while (que.size())
	{
		current = que.front();
		que.pop();

		if (used.find(current) != used.end()) continue;

		used.insert(current);

		GetNeighbours(map, neighbours, current.x, current.y);

		//adding available neighbours

		for (const auto &neighbour : neighbours)
		{
			if (used.find(neighbour) == used.end())
			{
				que.push(neighbour);
			}
		}
	}
	//return the last
	return current;
}

void Backtrack(std::vector<std::vector<int>> &LeeMatrix, const Matrix & map, coord begin, coord target, std::queue<coord> &path)
{
	coord current = begin;

	while (current != target)
	{
		path.push(current);
		current = GetPrevious(LeeMatrix, map, current);
	}
	path.push(current);
}

coord GetPrevious(std::vector<std::vector<int>> &LeeMatrix, const Matrix &map, coord begin)
{
	//going DOWN
	if (begin.y < (LeeMatrix.size() - 1) &&
		(LeeMatrix[begin.y][begin.x] - 1) == LeeMatrix[begin.y + 1][begin.x] &&
		map[begin.y][begin.x][BOTTOM_WALL] == 0 && map[begin.y + 1][begin.x][TOP_WALL] == 0)
		return coord(begin.x, begin.y + 1);

	//going UP
	else if (begin.y > 0 &&
		(LeeMatrix[begin.y][begin.x] - 1) == LeeMatrix[begin.y - 1][begin.x] &&
		map[begin.y][begin.x][TOP_WALL] == 0 && map[begin.y - 1][begin.x][BOTTOM_WALL] == 0)
		return coord(begin.x, begin.y - 1);

	//going RIGHT
	else if (begin.x < (LeeMatrix[begin.y].size() - 1) &&
		(LeeMatrix[begin.y][begin.x] - 1) == LeeMatrix[begin.y][begin.x + 1] &&
		map[begin.y][begin.x][RIGHT_WALL] == 0 && map[begin.y][begin.x + 1][LEFT_WALL] == 0)
		return coord(begin.x + 1, begin.y);

	//going LEFT
	if (begin.x > 0 &&
		(LeeMatrix[begin.y][begin.x] - 1) == LeeMatrix[begin.y][begin.x - 1] &&
		map[begin.y][begin.x][LEFT_WALL] == 0 && map[begin.y][begin.x - 1][RIGHT_WALL] == 0)
		return coord(begin.x - 1, begin.y);

	return begin;
}

void ConstructPaths(const Matrix &map, const coord &player, std::vector<Enemy>& enemies)
{
	std::vector<std::vector<int>> LeeMatrix;

	LeeMatrix.resize(map.size());
	int rowSize = map[0].size();

	for (auto & row : LeeMatrix)
		row.resize(rowSize);

	LeeMatrix[player.y][player.x] = 1;

	std::unordered_set <coord> used;


	std::queue<coord> que;

	que.push(player);

	coord current(player);
	std::vector<coord> neighbours;

	while (que.size())
	{
		current = que.front();
		que.pop();

		//if used
		if (used.find(current) != used.end()) continue;
		used.insert(current);


		GetNeighbours(map, neighbours, current.x, current.y);

		int neighboursCount = neighbours.size();


		//adding available neighbours
		for (size_t i = 0; i < neighboursCount; i++)
		{
			// if not used
			if (used.find(neighbours[i]) == used.end())
			{
				LeeMatrix[neighbours[i].y][neighbours[i].x] = LeeMatrix[current.y][current.x] + 1;
				que.push(neighbours[i]);
			}
			else
			{
				continue;
			}


			for (auto &enemy : enemies)
			{
				if (!enemy.IsUpToDate() && neighbours[i] == enemy.GetCoord())
				{
#ifdef DEBUG
					std::cout << "Route matrix:";
					for (auto row : LeeMatrix)
					{
						std::cout << '\n';
						for (auto cell : row)
							std::cout << cell << '\t';
					}
					std::cout << '\n';
#endif // DEBUG


					std::queue<coord> path;
					Backtrack(LeeMatrix, map, neighbours[i], player, path);
					enemy.UpdateRoute(path);
				}
			}	// for(auto &enemy : enemies)
		}	// !for(auto &neighbour : neighbours)
	}
}