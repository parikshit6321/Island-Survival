#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;

class Camera
{
public:
	Camera(ISceneManager* smgr);
	ICameraSceneNode* getNode();

private:
	ICameraSceneNode* node;
};

