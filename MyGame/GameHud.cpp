#include "GameHud.h"

GameHud::GameHud(IrrlichtDevice* irrDevice, ISceneManager* manager, IVideoDriver* videoDriver)
{
	device = irrDevice;
	smgr = manager;
	driver = videoDriver;
	guienv = device->getGUIEnvironment();
}

void GameHud::displayHealthBar(u8 health)
{
	if (health < 0)
	{
		return;
	}
	driver->draw2DRectangle(rect<s32>(30, 400 - (3 * health), 40, 400), SColor(255, 255, 0, 0), SColor(255, 255, 0, 0), SColor(255, 255, 0, 0), SColor(255, 255, 0, 0));
}

void GameHud::displayManaBar(u8 mana)
{
	if (mana < 0)
	{
		return;
	}
	driver->draw2DRectangle(rect<s32>(600, 400 - (3 * mana), 610, 400), SColor(255, 0, 0, 255), SColor(255, 0, 0, 255), SColor(255, 0, 0, 255), SColor(255, 0, 0, 255));
}