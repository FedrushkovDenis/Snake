#include "Game.hpp"
#include "Field.hpp"
#include <Windows.h>
#include "Stuff.h"

Game::~Game() 
{
	//field.~Field();
}

Game::Game()
{
	points = 0;
}

void Game::snakeTeleport(int x, int y)
{
	snake.x = x;
	snake.y = y;
}

int Game::UserControl(char w, char s, char a, char d)
{
	POINT oldPoint;
	oldPoint.x = snake.x;
	oldPoint.y = snake.y;

	if (GetKeyState(w) < 0 && snake.dir != dirDown)
		snake.dir = dirUp;
	if (GetKeyState(a) < 0 && snake.dir != dirRight)
		snake.dir = dirLeft;
	if (GetKeyState(s) < 0 && snake.dir != dirUp)
		snake.dir = dirDown;
	if (GetKeyState(d) < 0 && snake.dir != dirLeft)
		snake.dir = dirRight;

	if (snake.dir == dirLeft)
		snake.x--;
	if (snake.dir == dirRight)
		snake.x++;
	if (snake.dir == dirUp)
		snake.y--;
	if (snake.dir == dirDown)
		snake.y++;

	if (field.getCharField()[snake.y][snake.x] == PORTAL)
	{
		int place = 0;
		for (int i = 0; i < PORTALCOUNT; i++)
		{
			if (snake.x == field.getPortals()[i].x && snake.y == field.getPortals()[i].y)
			{
				place = i;
				break;
			}
		}
		snakeTeleport(field.getPortals()[abs(place - 3)].x, field.getPortals()[abs(place - 3)].y);
	}

	if (field.getCharField()[snake.y][snake.x] == FRUIT)
	{
		snake.addTailSegment(oldPoint.x, oldPoint.y);
		while (1)
		{
			char** ptrField = field.getCharField();
			short x = rand() % COLUMNS;
			short y = rand() % ROWS;
			if (x != 0 && x != (field.getColumns() - 1) && y != 0 && y != (field.getRows() - 1) &&
				ptrField[y][x] != '#' && ptrField[y][x] != '|' &&
				ptrField[y][x] != '-' && ptrField[y][x] != 'V' &&
				ptrField[y][x] != 'A' && ptrField[y][x] != '<' &&
				ptrField[y][x] != '>' && ptrField[y][x] != PORTAL)
			{
				field.addFruit(x, y);
				break;
			}
		}
		
	}
	else snake.MoveTail(oldPoint.x, oldPoint.y);

	if ((snake.x <= 0) || (snake.x >= field.getColumns()-1) ||
		(snake.y <= 0) || (snake.y >= field.getRows()-1)	||
		field.getCharField()[snake.y][snake.x] == TAIL /*|| field.getCharField()[snake.y][snake.x] == '-'*/)
		return 1;
	return 0;
}