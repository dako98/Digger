#ifndef _ALGORITHMS_
#define _ALGORITHMS_


#include <random>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Field.h"
#include "Constants.h"
#include "Enemy.h"

//srand(0);
void _RandomDFS(Matrix &map, int debth, int x, int y, bool &done);
void RandomDFS(Matrix &map, int debth, int beginX, int beginY);
void ConnectCells(Matrix &map, coord cell1, coord cell2);
void GetUnvisitedNeighbours(Matrix &map, std::vector<coord> &neightbours, int x, int y);
void GetNeighbours(Matrix &map, std::vector<coord> &neighbours, int x, int y);
coord FarthestCell(Matrix &map, coord begin);
void ConstructPaths(Matrix &map, coord player, std::vector<Enemy> &enemies);




#endif // !_ALGORITHMS_
