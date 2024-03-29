#ifndef _FIELD_
#define _FIELD_

#include <bitset>
#include <vector>
#include <SDL_image.h>

#include "Constants.h"
#include "ResourceLoader.h"
#include "Enemy.h"
#include "Player.h"


//using Matrix = std::vector<std::vector<std::bitset<BITS_IN_CELL>>>;


class Field
{
public:
	Field(SDL_Renderer* renderer);

	void Print() const;
	bool Update(int direction);
	void SpawnEnemy();

	void Reset();


	~Field();

private:

	TextureManager textures;

	SDL_Renderer * renderer;

	Matrix grid;

	coord monsterSpawner;
	std::vector<Enemy> enemies;
//	std::vector<Bag> bags;		//TODO


	Player player;
	coord previousPlayerPos;
	int gems;

};








#endif // !_FIELD_
