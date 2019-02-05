#ifndef _ALGORITHMS_
#define _ALGORITHMS_


//#include <random>
#include <ctime>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Field.h"
#include "Constants.h"
#include "Enemy.h"


void RandomDFS(Matrix &map, int debth, coord begin);

void ConnectCells(Matrix &map, coord cell1, coord cell2);

void GetUnvisitedNeighbours(Matrix &map, std::vector<coord> &neightbours, int x, int y);

void GetNeighbours(const Matrix &map, std::vector<coord> &neighbours, int x, int y);

void _RandomDFS(Matrix &map, int debth, int x, int y, bool &done);

coord FarthestCell(Matrix &map, coord begin);

void Backtrack(std::vector<std::vector<int>> &LeeMatrix, const Matrix &map, coord begin, coord target, std::queue<coord> &path);

coord GetPrevious(std::vector<std::vector<int>> &LeeMatrix, const Matrix &map, coord begin);

void ConstructPaths(const Matrix &map,const coord &player, std::vector<Enemy> &enemies);




#endif // !_ALGORITHMS_
