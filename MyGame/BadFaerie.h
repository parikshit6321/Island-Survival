#pragma once

#include <irrlicht.h>
#include "Enemy.h"
#include "PowerBallEnemy.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

class BadFaerie : public Enemy
{
public:
	BadFaerie(vector3df position, f32 newSpeed, ISceneManager* manager, Player* target, IrrlichtDevice* irrDevice, list<GameObject*> * updateListPtr, IVideoDriver* videoDriver);
	virtual void update(f32 deltaTime);
	virtual void attack();
	virtual void dodge(f32 deltaTime);
	virtual void run(f32 deltaTime);
	virtual void loadModel(IAnimatedMesh* mesh, ITexture* texture);
	bool seesPowerBall();
	bool listHasPowerBall();

private:
	f32 dodgeStart;
	f32 lastAttack;
	IVideoDriver* driver;
	list<GameObject*> * listPtr;
};

