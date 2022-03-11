#include "..\Singleton\Singleton.hpp"
#include "..\WindowClasses\WindowClass.hpp"

Singleton::Singleton() {}

Game* Singleton::myGame = 0;
MainMenu* Singleton::myMenu = 0;
GameWindow* Singleton::myGameWindow = 0;

// Game/Logic

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



// Menu/Window

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



// Game/Window

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