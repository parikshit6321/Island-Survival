#pragma once

#include "Enemy.h"

class Wraith : public Enemy
{
public:
	Wraith(vector3df position, f32 newSpeed, ISceneManager* manager, Player* playerTarget, IrrlichtDevice* irrDevice, list<GameObject*> * updateListPtr, IVideoDriver* videoDriver);
	virtual void update(f32 deltaTime);
	virtual void attack();
	virtual void dodge(f32 deltaTime);
	virtual void run(f32 deltaTime);
	virtual void loadModel(IAnimatedMesh* mesh, ITexture* texture);

private:
	IVideoDriver* driver;
	list<GameObject*> * listPtr;
	f32 lastAttack;
	f32 lastTeleport;
};

