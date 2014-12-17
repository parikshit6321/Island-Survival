#pragma once
#include "GameObject.h"
#include "Player.h"

enum EnemyState
{
	ENEMY_RUN,
	ENEMY_ATTACK,
	ENEMY_DODGE,
	ENEMY_IDLE
};

enum AttackRating
{
	POWER_BALL = 1,
	MONSTER_ATTACK
};

class Enemy : public GameObject
{
public:
	Enemy(vector3df newPosition, f32 newSpeed, ISceneManager* manager, Player* enemyTarget);
	virtual void update(f32 deltaTime);
	virtual void attack() = 0;
	virtual void dodge(f32 deltaTime) = 0;
	virtual void run(f32 deltaTime) = 0;
	virtual void loadModel(IAnimatedMesh* mesh, ITexture* texture);
	ISceneNode* getNode();
	virtual void facePlayer();
	virtual void pushBack();
	virtual vector3df getPosition();

protected:
	IAnimatedMeshSceneNode* node;
	Player* target;
	vector3df facingDirection;
	EnemyState currentState;
	bool bPushedBack;
	f32 pushStart;
	IrrlichtDevice* device;
};

