#ifndef _SINGLETON
#define _SINGLETON

#include "WindowClass.hpp"
#include "Game.hpp"

class Singleton
{
private:
	static Game* myGame;
	static MainMenu* myMenu;
	static GameWindow* myGameWindow;

	Singleton(const Singleton& root) = delete;
	Singleton& operator=(const Singleton&) = delete;
public:
	static Game* getGame();
	static void deleteGame();
	static void createGame();

	static void createMainMenu();
	static MainMenu* getMainMenu();

	static void createGameWindow();
	static GameWindow* getGameWindow();
protected:
	Singleton();
};

#endif // !_SINGLETON
