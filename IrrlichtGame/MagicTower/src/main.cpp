#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

int main()
{
	IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);
	if (!device)
		return 1;
	device->setWindowCaption(L"Hello Irrlicht!");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	while (device->run())
	{
		driver->beginScene(true, true, SColor(255, 25, 25, 25));
		smgr->drawAll();
		driver->endScene();
	}

	device->drop();
	return 0;
}