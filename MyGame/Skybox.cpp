#include "Skybox.h"

Skybox::Skybox(ISceneManager* smgr, IVideoDriver* driver)
{
	node = smgr->addSkyBoxSceneNode(driver->getTexture("Textures/up.png"), driver->getTexture("Textures/down.png"), driver->getTexture("Textures/right.png"), driver->getTexture("Textures/left.png"), driver->getTexture("Textures/front.png"), driver->getTexture("Textures/back.png"));
	light = smgr->addLightSceneNode();
	
	SLight lightData;
	lightData.Type = ELT_DIRECTIONAL;
	lightData.CastShadows = true;
	lightData.Direction = vector3df(1, -1, 0).normalize();

	light->setLightType(ELT_DIRECTIONAL);
	light->setLightData(lightData);
	light->enableCastShadow();
}

ISceneNode* Skybox::getNode()
{
	return node;
}