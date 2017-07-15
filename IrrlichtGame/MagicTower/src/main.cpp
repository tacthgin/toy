#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

int main()
{
	IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);
	if (!device)
		return 1;
	device->setWindowCaption(L"Hello Irrlicht!");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	video::ITexture* cat = driver->getTexture("../resources/images/cat.jpg");
	guienv->addImage(cat, vector2d<s32>(100, 100));

	while (device->run())
	{
		driver->beginScene(true, true, SColor(255, 25, 25, 25));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}

	device->drop();
	return 0;
}