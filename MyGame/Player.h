#pragma once

#include <irrlicht.h>
#include "Camera.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class PowerBall;

#define POWERBALL_COST				20
#define PUSH_COST					30
#define TELEPORT_COST				30
#define MANA_REGENERATE_PER_SEC		5
#define PICKUP_HEAL					30

enum State
{
	IDLE,
	ATTACK,
	RUNNING
};

class Player
{
public:
	Player(IrrlichtDevice* irrDevice, ISceneManager* smgr, IVideoDriver* driver, Camera* camera);
	IAnimatedMesh* getMesh();
	IAnimatedMeshSceneNode* getNode();
	vector3df getPosition();
	vector3df getDirection();
	void moveForward(f32 deltaTime);
	void moveBackward(f32 deltaTime);
	void turnLeft(f32 deltaTime);
	void turnRight(f32 deltaTime);
	void strafeLeft(f32 deltaTime);
	void strafeRight(f32 deltaTime);
	void setIdleAnimation();
	void setRunningAnimation();
	void setAttackAnimation();
	PowerBall* Attack();
	bool push();
	void teleport();
	void takeDamage(u8 attackRating);
	void kill();
	bool isDead();
	void takePickup();
	u8 getHealth();
	u8 getMana();
	void incrementMana();
	
private:
	f32 lastAttack;
	f32 lastPush;
	f32 lastTeleport;
	f32 cameraDistance;
	State state;
	f32 speed;
	IrrlichtDevice* device;
	ISceneManager* smgr;
	IVideoDriver* driver;
	IAnimatedMesh* mesh;
	IAnimatedMeshSceneNode* node;
	vector3df forwardDirection;
	u8 health;
	u8 mana;
	Camera* camera;
};