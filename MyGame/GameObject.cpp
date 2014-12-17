#include "GameObject.h"

GameObject::GameObject()
{
	bNeedsUpdate = true;
	bIsActive = true;
}

GameObject::GameObject(vector3df position, f32 objectSpeed, ISceneManager* manager)
{
	origPosition = position;
	bNeedsUpdate = true;
	smgr = manager;
	bIsActive = true;
	setSpeed(objectSpeed);
}

vector3df GameObject::getPosition()
{
	return vector3df(0, 0, 0);
}

ISceneNode* GameObject::getNode()
{
	return NULL;
}

bool GameObject::isActive()
{
	return bIsActive;
}

void GameObject::kill()
{
	bIsActive = false;
}

f32 GameObject::getSpeed()
{
	return speed;
}

void GameObject::setSpeed(f32 newSpeed)
{
	if (newSpeed < 0)
	{
		speed = newSpeed * -1.0f;
	}
	else
	{
		speed = newSpeed;
	}
}

void GameObject::update(f32 deltaTime)
{
}

bool GameObject::needsUpdate()
{
	return bNeedsUpdate;
}

void GameObject::pushBack()
{
}