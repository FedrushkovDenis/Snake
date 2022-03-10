#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <locale.h>
#include "Game.hpp"
#include "Singleton.hpp"
#include "WindowClass.hpp"
#include <Windows.h>

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

BOOL ShowConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	return TRUE;
}

int main()
{
	/*Singleton::createMainMenu();
	Singleton::createGameWindow();

	MainMenu* myMenu = Singleton::getMainMenu();
	GameWindow* myGameWindow = Singleton::getGameWindow();

	myMenu->setSettings(L"MyMainMenu");
	myGameWindow->setSettings(L"MyGameWindow");

	myMenu->StartWindow();

	return 0;*/

	ShowConsoleCursor(FALSE);

	Singleton::createGame();
	Game* myGame = Singleton::getGame();
	Builder myBuilder(ROWS, COLUMNS);

	myBuilder.buildbyReference(&Singleton::getGame()->field);

	myGame->snake.ConnectToMap(myGame->field.getCharField());

	myGame->snake.Init(3, 8, dirDown);
	myGame->snake.addTailSegment(3, 4);
	myGame->snake.addTailSegment(3, 5);
	myGame->snake.addTailSegment(3, 6);
	myGame->snake.addTailSegment(3, 7);

	myGame->field.CreatePortals();

	for (short i = 0; i < PORTALCOUNT; i++)
	{
		myGame->field.addPortal(myGame->field.getPortals()[i]);
	}

	myGame->field.addFruit(10, 10);
	myGame->field.addFruit(12, 12);
	myGame->field.addFruit(14, 14);

	myGame->snake.drawOnMap();
	myGame->field.printField();
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		gotoxy(0, 0);
		if (myGame->UserControl('W', 'S', 'A', 'D'))
		{
			myGame->snake.Init(3, 8, dirDown);
			myGame->snake.addTailSegment(3, 4);
			myGame->snake.addTailSegment(3, 5);
			myGame->snake.addTailSegment(3, 6);
			myGame->snake.addTailSegment(3, 7);
		}
		myGame->field.clearField();

		myGame->snake.drawOnMap();
		myGame->field.printField();
		Sleep(80);
	}

	Singleton::deleteGame();

	return 0;
	


	//Singleton::getGame().





	//Singletone mysing(5,5);
	//Game myGame;
	////myGame.printField();
	//myGame.field.printField();
}

//void setField(Field* field, short rows, short columns)
//{
//	field->rows = rows;
//	field->columns = columns;
//	field->field = (char**)malloc(field->rows * sizeof(char*));
//	for (int i = 0; i < field->rows; i++)
//	{
//		field->field[i] = (char*)malloc(field->columns * sizeof(char));
//	}
//	for (int i = 0; i < field->rows; i++)
//	{
//		for (int j = 0; j < field->columns; j++)
//		{
//			field->field[i][j] = ' ';
//			if (i == 0 || j == 0 || i == (field->rows - 1) || j == (field->columns - 1))
//				field->field[i][j] = '#';
//		}
//	}
//}
//
//void printField(Field* field)
//{
//	for (int i = 0; i < field->rows; i++)
//	{
//		for (int j = 0; j < field->columns; j++)
//		{
//			printf("%c", field->field[i][j]);
//		}
//		printf("\n");
//	}
//}
//
//void DestroyField(Field* field)
//{
//	for (int i = 0; i < field->rows; i++)
//	{
//		free(field->field[i]);
//	}
//	free(field->field);
//}
//
//void setShape(Field* field)
//{
//
//}
//
//int main()
//{
//	Snake mySnake;
//	Field myField;
//	setField(&myField, 15, 15);
//	printField(&myField);
//	DestroyField(&myField);
//}