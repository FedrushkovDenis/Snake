// Чтобы посмотреть на систему под капотом раскомментируйте DEBUG

//#define DEBUG

#ifdef DEBUG

#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#else

//#pragma comment(linker, "/SUBSYSTEM:WINDOWS")

#endif // DEBUG

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <locale.h>
#include "Game/Game.hpp"
#include "Singleton/Singleton.hpp"
#include "WindowClasses/WindowClass.hpp"
#include <Windows.h>
#ifdef DEBUG

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
	system("pause");
	return 0;
}

#else 

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hpi, LPSTR cmdline, int ss)
{
	Singleton::hInst = hInst; // Сохраняем дескриптор модуля для дальнейшей загрузки ресурсов. Подробнее https://docs.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point

	Singleton::createGame();
	Singleton::createMainMenu();
	Singleton::createGameWindow();

	Game* myGame = Singleton::getGame();
	Builder myBuilder(ROWS, COLUMNS);

	myBuilder.buildbyReference(&Singleton::getGame()->field);

	MainMenu* myMenu = Singleton::getMainMenu();
	GameWindow* myGameWindow = Singleton::getGameWindow();

	myMenu->setSettings(L"MyMainMenu");
	myGameWindow->setSettings(L"MyGameWindow");

	myMenu->StartWindow();

	return 0;
}

#endif // DEBUG


