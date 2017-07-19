#include "Game.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

Game* Game::s_instance = nullptr;

Game * Game::getInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new(Game);
	}
		
	return s_instance;
}

void Game::destoryInstance()
{
	if (s_instance)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

irr::IrrlichtDevice * Game::getDevice()
{
	return _device;
}

irr::video::IVideoDriver * Game::getDriver()
{
	return _driver;
}

irr::scene::ISceneManager * Game::getSceneManager()
{
	return _sceneMgr;
}

irr::gui::IGUIEnvironment * Game::getGUIEnvironment()
{
	return _guiEnv;
}

bool Game::initWindow(int width, int height, const wchar_t* title)
{
	_device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
		false, false, false, 0);
	if (!_device)
		return false;
	_device->setWindowCaption(title);

	_driver = _device->getVideoDriver();
	_sceneMgr = _device->getSceneManager();
	_guiEnv = _device->getGUIEnvironment();

	return true;
}

void Game::loop()
{
	while(_device->run())
	{
		_driver->beginScene(true, true, SColor(255, 25, 25, 25));
		_sceneMgr->drawAll();
		_guiEnv->drawAll();
		_driver->endScene();
	}

	_device->drop();
}
