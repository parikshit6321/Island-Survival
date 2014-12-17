#pragma once

#include "Enemy.h"

class Monster : public Enemy
{
public:
	Monster(vector3df newPosition, f32 newSpeed, ISceneManager* manager, Player* enemyTarget, IrrlichtDevice* irrDevice);
	virtual void update(f32 deltaTime);
	virtual void attack();
	virtual void dodge(f32 deltaTime);
	virtual void run(f32 deltaTime);
	virtual void loadModel(IAnimatedMesh* mesh, ITexture* texture);

private:
	f32 lastAttack;
};

