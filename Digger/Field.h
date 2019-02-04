#ifndef _FIELD_
#define _FIELD_

#include <bitset>
#include <vector>
#include <SDL_image.h>


#include "Constants.h"

using Matrix = std::vector<std::vector<std::bitset<BITS_IN_CELL>>>;


class Field
{
public:
	Field();

	void Print(SDL_Renderer* renderer) const;





	~Field();

private:

	std::vector < SDL_Texture*> textures;


	Matrix grid;
//	std::vector<Enemy> enemies;	//TODO
//	std::vector<Bag> bags;		//TODO


};








#endif // !_FIELD_
