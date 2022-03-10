#include "Singleton.hpp"
#include "WindowClass.hpp"

Singleton::Singleton() {}

Game* Singleton::myGame = 0;
MainMenu* Singleton::myMenu = 0;
GameWindow* Singleton::myGameWindow = 0;

Game* Singleton::getGame()
{
	if (myGame)
		return myGame;
	else return 0;
}

void Singleton::createGame()
{
	if (!myGame)
	{
		myGame = new Game;
	}
}

void Singleton::deleteGame()
{
	if (myGame)
		delete myGame;
}


MainMenu* Singleton::getMainMenu()
{
	if (myMenu)
		return myMenu;
	else return 0;
}

void Singleton::createMainMenu()
{
	if (!myMenu)
	{
		myMenu = new MainMenu;
	}
}

GameWindow* Singleton::getGameWindow()
{
	if (myGameWindow)
		return myGameWindow;
	else return 0;
}

void Singleton::createGameWindow()
{
	if (!myGameWindow)
	{
		myGameWindow = new GameWindow;
	}
}