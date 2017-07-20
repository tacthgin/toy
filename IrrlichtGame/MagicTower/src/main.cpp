#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	if (!Game::getInstance()->initWindow(640, 480, L"Ä§Ëþ"))
	{
		cout << "Init Irrlicht Failed" << endl;
		return 1;
	}

	Game::getInstance()->loop();

	return 0;
}