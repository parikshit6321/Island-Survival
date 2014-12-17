#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

#pragma once

class Terrain
{
public:
	Terrain(ISceneManager* smgr, IVideoDriver* driver);
	ITerrainSceneNode* getNode();

private:
	ITerrainSceneNode* terrain;
};

