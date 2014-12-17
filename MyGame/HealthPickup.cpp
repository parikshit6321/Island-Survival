#include "HealthPickup.h"

HealthPickup::HealthPickup(vector3df position, f32 speed, ISceneManager* manager, IVideoDriver* videoDriver) : driver(videoDriver), GameObject(position, speed, manager)
{
	node = smgr->addCubeSceneNode(20.0f, NULL, -1, vector3df(origPosition));
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture(0, driver->getTexture("Textures/Cube.bmp"));
}

bool HealthPickup::isNear(vector3df position)
{
	if ((origPosition - position).getLengthSQ() < 2500)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void HealthPickup::remove()
{
	node->remove();
}
