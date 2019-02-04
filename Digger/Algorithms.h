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
coord FarthestCell(Matrix &map, coord begin);


#endif // !_ALGORITHMS_
