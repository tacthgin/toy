#ifndef _GAME_H_
#define _GAME_H_

#include <irrlicht/irrlicht.h>

class Game
{
public:
	static Game* getInstance();
	void destoryInstance();
	Game(const Game&) = delete;
	Game operator=(const Game&) = delete;
	Game(const Game&&) = delete;
	Game operator=(const Game&&) = delete;
public:
	irr::IrrlichtDevice* getDevice();
	irr::video::IVideoDriver* getDriver();
	irr::scene::ISceneManager* getSceneManager();
	irr::gui::IGUIEnvironment* getGUIEnvironment();

	bool initWindow(int width = 640, int height = 480, const wchar_t* title = L"");
	void loop();
private:
	Game() {}
private:
	static Game* s_instance;
	irr::IrrlichtDevice* _device;
	irr::video::IVideoDriver* _driver;
	irr::scene::ISceneManager* _sceneMgr;
	irr::gui::IGUIEnvironment* _guiEnv;
};

#endif // !_GAME_H_

