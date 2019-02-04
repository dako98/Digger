#ifndef _FIELD_
#define _FIELD_

#include <bitset>
#include <vector>
#include <SDL_image.h>

#include "Constants.h"
#include "ResourceLoader.h"
#include "Enemy.h"


//using Matrix = std::vector<std::vector<std::bitset<BITS_IN_CELL>>>;


class Field
{
public:
	Field(SDL_Renderer* renderer);

	void Print(SDL_Renderer* renderer) const;
	void Update();




	~Field();

private:

	TextureManager textures;


	Matrix grid;

	coord monsterSpawner;
	std::vector<Enemy> enemies;	//TODO
//	std::vector<Bag> bags;		//TODO


	coord Player;


};








#endif // !_FIELD_
