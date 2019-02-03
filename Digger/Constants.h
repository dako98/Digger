#ifndef _CONSTANTS_
#define _CONSTANTS_


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int CELL_WIDTH = 50;
const int CELL_HEIGHT = 50;


//Couldn't make a structure with two structures inside
const int GAME_FIELD_BEGIN_X = 0;
const int GAME_FIELD_BEGIN_Y = 0;
const int GAME_FIELD_END_X = 0;
const int GAME_FIELD_END_Y = 0;


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
	DIAMOND,			//2
	GEM,				//3
	TOP_WALL,			//4
	LEFT_WALL,			//5
	BOTTOM_WALL,		//6
	RIGHT_WALL			//7
};





#endif // !_CONSTANTS_
