#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	if (Game::getInstance()->initWindow(640, 480, L"ħ��"))
	{
		Game::getInstance()->loop();
	}else
	{
		cout << "Init Irrlicht Failed" << endl;
	}
	return 0;
}