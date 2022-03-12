#ifndef _SNAKE
#define _SNAKE

#include <Windows.h>
#include "..\Stuff.hpp"

enum Direction {dirUp, dirLeft, dirDown, dirRight};

class Snake
{
private:
	POINT tail[lenLim];

public:
	Snake(char** map);
	Snake() {};

	void Init(int rows, int columns, Direction dir);
	void ConnectToMap(char** map);
	void drawOnMap();

	void addTailSegment(int _x, int _y);
	void MoveTail(int _x, int _y);

	char Head;
	int x, y;
	char** map;
	Direction dir;
	int len;
};

#endif // !_SNAKE
