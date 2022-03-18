#include "..\Snake\Snake.hpp"

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
		Head = '>';
		map[y][x] = Head;
	}
	else if (dir == dirLeft)
	{
		Head = '<';
		map[y][x] = Head;
	}
	else if (dir == dirDown)
	{
		Head = 'V';
		map[y][x] = Head;
	}
	else if (dir == dirUp)
	{
		Head = 'A';
		map[y][x] = Head;
	}

	for (int i = 0; i < len; i++)
	{
		map[tail[i].y][tail[i].x] = TAIL;
	}
}
