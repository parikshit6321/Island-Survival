#include "Terrain.h"

Terrain::Terrain(ISceneManager* smgr, IVideoDriver* driver)
{
	terrain = smgr->addTerrainSceneNode("Textures/terrain-heightmap.bmp");
	terrain->setPosition(vector3df(0, 0, 0));
	terrain->setScale(vector3df(40, 0.5, 40));
	terrain->setMaterialFlag(EMF_LIGHTING, false);
	terrain->setMaterialTexture(0, driver->getTexture("Textures/terrain-texture.bmp"));
}

ITerrainSceneNode* Terrain::getNode()
{
	return terrain;
}