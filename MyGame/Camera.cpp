#include "Camera.h"


Camera::Camera(ISceneManager* smgr)
{
	node = smgr->addCameraSceneNode(0, vector3df(600, 110, 450), vector3df(0, 0, 0));
	node->setFarValue(42000.0f);
}

ICameraSceneNode* Camera::getNode()
{
	return node;
}
