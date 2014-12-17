#include "PowerBall.h"

PowerBall::PowerBall(ISceneManager* manager, IVideoDriver* driver, vector3df start, vector3df forwardDirection, f32 ballSpeed) : GameObject(start, ballSpeed, manager), direction(forwardDirection)
{
	node = smgr->addBillboardSceneNode();
	node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	node->setMaterialTexture(0, driver->getTexture("Textures/powerball.bmp"));
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	node->setPosition(vector3df(start.X - 5.0f, start.Y + 20.0f, start.Z));
}

void PowerBall::update(f32 deltaTime)
{
	if (bNeedsUpdate)
	{
		direction.normalize();
		node->updateAbsolutePosition();
		node->setPosition(node->getAbsolutePosition() + (speed * direction * deltaTime));
		node->updateAbsolutePosition();

		if ((node->getAbsolutePosition() - origPosition).getLengthSQ() > 1000000.0f)
		{
			bNeedsUpdate = false;
		}
	}
}

ISceneNode* PowerBall::getNode()
{
	return node;
}
