#ifndef _CONSTANTS_
#define _CONSTANTS_

#include <array>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int CELL_WIDTH = 50;
const int CELL_HEIGHT = 50;

const int VERTICAL_WALL_WIDTH = 10;
const int VERTICAL_WALL_HEIGTH = 50;

const int HORIZONTAL_WALL_WIDTH = 50;
const int HORIZONTAL_WALL_HEIGTH = 10;


//Couldn't make a structure with two structures inside

const int GAME_FIELD_BEGIN_X = 0;
const int GAME_FIELD_BEGIN_Y = 0;
const int GAME_FIELD_END_X = WINDOW_WIDTH;
const int GAME_FIELD_END_Y = WINDOW_HEIGHT;


const int CELLS_IN_ROW = WINDOW_WIDTH / CELL_WIDTH;
const int CELLS_IN_COL = WINDOW_HEIGHT / CELL_HEIGHT;

struct Color
{
	short red;
	short green;
	short blue;
	short opacity;
};

const Color MISSING_TEXTURE_COLOR = { 247, 0, 247, 0 };


const int BITS_IN_CELL = 8;

enum CellData
{
	DIFFICULTY = 1,		//0, 1
	GEM,				//2
	BAG,				//3
	TOP_WALL,			//4
	LEFT_WALL,			//5
	BOTTOM_WALL,		//6
	RIGHT_WALL			//7
};

enum Textures
{
	MISSING_TEXTURE,

	WALL_TEXTURE,
	NORMAL_DIRT_TEXTURE,
	HARD_DIRT_TEXTURE,
	NO_DIRT_TEXTURE,

	SPAWNER_TEXTURE,

	PLAYER_TEXTURE,
	ENEMY_TEXTURE,
	GEM_TEXTURE,
	BAG_TEXTURE,
	COINS_TEXTURE,

	GRAVE_TEXTURE,

	COUNT
};

const std::array<const char* const, Textures::COUNT> TEXTURE_PATHS = {
	"missing-texture.png",
	"wall.png",
	"dirt.png",
	"hard-dirt.png",
	"no-dirt.png",
	"spawner.png",
	"player.png",
	"enemy.png",
	"gem.png",
	"bag.png",
	"coins.png",
	"grave.png"
};

struct coord
{
	coord()
		:x(0)
		, y(0)
	{}

	coord(int x, int y)
		:x(x)
		, y(y)
	{}

	int x, y;
};


static bool operator==(const coord& lhs, const coord& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

template<>
struct std::hash<coord> 
{
	size_t operator()(const coord& key) const noexcept 
	{
		return std::hash<int>()(key.y * WINDOW_WIDTH + key.x);
	}
};





#endif // !_CONSTANTS_
