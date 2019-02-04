#include "Algorithms.h"


void RandomDFS(Matrix &map, int debth, int beginX, int beginY)
{
	bool done = false;
	_RandomDFS(map, debth, beginX, beginY, done);
}

void ConnectCells(Matrix &map, coord cell1, coord cell2)
{
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
	if (x - 1 > 0 && map[y][x - 1] == 0b11110000)
		neightbours.push_back(coord(x - 1, y));

	if (x + 1 < map[y].size() && map[y][x + 1] == 0b11110000)
		neightbours.push_back(coord(x + 1, y));

	if (y - 1 > 0 && map[y - 1][x] == 0b11110000)
		neightbours.push_back(coord(x, y - 1));

	if (y + 1 < map.size() && map[y + 1][x] == 0b11110000)
		neightbours.push_back(coord(x, y + 1));
}

void GetNeighbours(Matrix & map, std::vector<coord>& neightbours, int x, int y)
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

void ConstructPaths(Matrix & map, coord player, std::vector<Enemy>& enemies)
{
	int distance = 1;

	std::vector<std::vector<int>> LeeMatrix;

	LeeMatrix.resize(map.size());
	int rowSize = map[0].size();

	for (auto & row : LeeMatrix)
		row.resize(rowSize);

	LeeMatrix[player.y][player.x] = distance;

	distance++;

	std::unordered_set <coord> used;


	std::queue<coord> que;

	que.push(player);

	coord current(player);
	std::vector<coord> neighbours;

	while (que.size())
	{
		current = que.front();
		que.pop();

		if (used.find(current) != used.end()) continue;

		used.insert(current);

		GetNeighbours(map, neighbours, current.x, current.y);

		//adding available neighbours

		for (auto &neighbour : neighbours)
		{
			for (auto &enemy : enemies)
			{
				if (neighbour == enemy.GetCoord())
				{
					LeeMatrix[neighbour.y][neighbour.x] = distance;
					
					std::queue<coord> path;
					Backtrack(LeeMatrix, neighbour, player, path);
					enemy.UpdateRoute(path);
				}
			}

			if (used.find(neighbour) == used.end())
			{
				LeeMatrix[neighbour.y][neighbour.x] = distance;
				que.push(neighbour);
			}
		}
		distance++;
	}
}

void Lee(Matrix &map, coord begin, coord target, std::queue<coord> &path)
{
	int distance = 0;

	std::vector<std::vector<int>> LeeMatrix;

	LeeMatrix.resize(map.size());
	int rowSize = map[0].size();

	for (auto & row : LeeMatrix)
		row.resize(rowSize);

	LeeMatrix[begin.y][begin.x] = distance;

	distance++;

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

		for (auto &neighbour : neighbours)
		{
			LeeMatrix[neighbour.y][neighbour.x] = distance;

			if (neighbour == target)
			{
				Backtrack(LeeMatrix, target, begin, path);
			}

			if (used.find(neighbour) == used.end())
			{
				que.push(neighbour);
			}
		}
		distance++;
	}
}

void Backtrack(std::vector<std::vector<int>> &LeeMatrix, coord begin, coord target, std::queue<coord> &path)
{
	coord current = begin;

	while (current != target)
	{
		path.push(current);
		current = GetPrevious(LeeMatrix, current);
	}
	path.push(current);
}

coord GetPrevious(std::vector<std::vector<int>> &LeeMatrix, coord begin)
{
	if (begin.y < (LeeMatrix.size() - 1) && 
		(LeeMatrix[begin.y][begin.x] - 1) == LeeMatrix[begin.y + 1][begin.x])
		return coord(begin.x, begin.y + 1);

	else if (begin.y > 0 && 
		(LeeMatrix[begin.y][begin.x] - 1) == LeeMatrix[begin.y - 1][begin.x])
		return coord(begin.x, begin.y - 1);

	else if (begin.x < (LeeMatrix[begin.y].size() - 1) && 
		(LeeMatrix[begin.y][begin.x] - 1) == LeeMatrix[begin.y][begin.x + 1])
		return coord(begin.x + 1, begin.y);

	if (begin.x >0 && 
		(LeeMatrix[begin.y][begin.x] - 1) == LeeMatrix[begin.y][begin.x - 1])
		return coord(begin.x - 1, begin.y);

	return begin;
}