#ifndef _ALGORITHMS_
#define _ALGORITHMS_


#include <random>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Field.h"
#include "Constants.h"

//srand(0);
void _RandomDFS(Matrix &map, int debth, int x, int y, bool &done);
void RandomDFS(Matrix &map, int debth, int beginX, int beginY);
void ConnectCells(Matrix &map, coord cell1, coord cell2);
void GetNeighbours(Matrix &map, std::vector<coord> &neightbours, int x, int y);
coord FarthestCell(Matrix &map, coord begin, coord &farthest);



void RandomDFS(Matrix &map, int debth, int beginX, int beginY)
{
	bool done = false;
	_RandomDFS(map, debth, beginX, beginY, done);
}

void ConnectCells(Matrix &map, coord cell1, coord cell2)
{
	if (cell1.x==cell2.x)
	{
		map[cell1.x][std::min(cell1.y, cell2.y)][BOTTOM_WALL] = 0; 
		map[cell1.x][std::max(cell1.y, cell2.y)][TOP_WALL] = 0;
		return;
	}

	if (cell1.y == cell2.y)
	{
		map[std::min(cell1.x, cell2.x)][cell1.y][RIGHT_WALL] = 0;
		map[std::max(cell1.x, cell2.x)][cell1.y][LEFT_WALL] = 0;
		return;
	}
}

void GetNeighbours(Matrix &map, std::vector<coord> &neightbours, int x, int y)
{
	neightbours.erase(neightbours.begin(), neightbours.end());
	//get all unvisited neighbours
	if (x - 1 >= 0 && map[x - 1][y] == 0b00001111)					neightbours.push_back(coord(x - 1, y));
	if (x + 1 <= map[y].size() && map[x + 1][y] == 0b00001111)		neightbours.push_back(coord(x + 1, y));
	if (y - 1 >= 0 && map[x][y - 1] == 0b00001111)					neightbours.push_back(coord(x, y - 1));
	if (y + 1 <= map[x].size() && map[x][y + 1] == 0b00001111)		neightbours.push_back(coord(x, y + 1));
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

		GetNeighbours(map, neightbours, x, y);
		

		//if if got stuck, it will choose a new path
		while (neightbours.size() > 0 && !done)
		{
			int direction = rand() % neightbours.size();
			
			ConnectCells(map, coord(x, y), neightbours[direction]);

			_RandomDFS(map, debth - 1, neightbours[direction].x, neightbours[direction].y, done);
			GetNeighbours(map, neightbours, x, y);
		}
	}
}

coord FarthestCell(Matrix &map, coord begin)
{

	std::unordered_set<coord> used;


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

#endif // !_ALGORITHMS_
