#pragma once
#include "GameObject.h"



class HealthPickup : public GameObject
{
public:
	HealthPickup(vector3df position, f32 speed, ISceneManager* manager, IVideoDriver* videoDriver);
	bool isNear(vector3df position);
	void remove();

private:
	IMeshSceneNode* node;
	IVideoDriver* driver;
};

