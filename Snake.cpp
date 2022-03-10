#include "Snake.hpp"

Snake::Snake(char** map)
{
	this->map = map;
}

void Snake::Init(int x, int y, Direction dir)
{
	this->x = x;
	this->y = y;
	this->dir = dir;
	this->len = 0;
}

void Snake::ConnectToMap(char** map)
{
	this->map = map;
	Init(0, 0, dirRight);
}

void Snake::MoveTail(int _x, int _y)
{
	for (int i = len-1; i >= 0; i--)
	{
		tail[i + 1] = tail[i];
	}
	tail[0].x = _x;
	tail[0].y = _y;
}

void Snake::addTailSegment(int _x, int _y)
{
	MoveTail(_x, _y);
	len++;
	if (len >= lenLim)
		len = lenLim - 1;
}

void Snake::drawOnMap()
{
	if (dir == dirRight)
	{
		map[y][x] = '>';
	}
	else if (dir == dirLeft)
	{
		map[y][x] = '<';
	}
	else if (dir == dirDown)
	{
		map[y][x] = 'V';
	}
	else if (dir == dirUp)
	{
		map[y][x] = 'A';
	}

	for (int i = 0; i < len; i++)
	{
		map[tail[i].y][tail[i].x] = TAIL;
		/*if (dir == dirRight || dir == dirLeft)
			map[tail[i].y][tail[i].x] = '-';
		else
			map[tail[i].y][tail[i].x] = '|';*/
	}
}

//void Snake::drawOnMap()
//{
//	if (dir == dirRight)
//	{
//		map[y][x] = HEAD;
//	}
//	else if (dir == dirLeft)
//	{
//		map[y][x] = HEAD;
//	}
//	else if (dir == dirDown)
//	{
//		map[y][x] = HEAD;
//	}
//	else if (dir == dirUp)
//	{
//		map[y][x] = HEAD;
//	}
//
//	for (int i = 0; i < len; i++)
//	{
//		if (dir == dirRight || dir == dirLeft)
//			map[tail[i].y][tail[i].x] = TAIL;
//		else
//			map[tail[i].y][tail[i].x] = TAIL;
//	}
//}