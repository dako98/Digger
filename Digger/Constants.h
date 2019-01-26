#ifndef _CONSTANTS_
#define _CONSTANTS_


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

struct Color
{
	short red;
	short green;
	short blue;
	short opacity;
};

const Color MISSING_TEXTURE_COLOR = { 247,0,247,0 };



#endif // !_CONSTANTS_
