#include <math.h>
#include "Player.h"
#include "PowerBall.h"


Player::Player(IrrlichtDevice* irrDevice, ISceneManager* manager, IVideoDriver* videoDriver, Camera* myCamera) : device(irrDevice), smgr(manager), driver(videoDriver), camera(myCamera)
{
	lastTeleport = 0.0f;
	lastPush = 0.0f;
	lastAttack = 0.0f;
	speed = 0.2f;
	health = 100;
	mana = 100;

	mesh = smgr->getMesh("Models/sydney.md2");
	node = smgr->addAnimatedMeshSceneNode(mesh);
	node->setMaterialTexture(0, driver->getTexture("Textures/sydney.bmp"));
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setPosition(vector3df(600, 60, 600));
	node->setRotation(vector3df(0, -90, 0));
	node->addShadowVolumeSceneNode();

	camera->getNode()->updateAbsolutePosition();
	node->updateAbsolutePosition();

	camera->getNode()->setTarget(node->getAbsolutePosition());

	// Calculating forwardDirection.
	vector3df temp = vector3df(camera->getNode()->getAbsolutePosition().X, (camera->getNode()->getAbsolutePosition().Y) - (node->getAbsolutePosition().Y), camera->getNode()->getAbsolutePosition().Z);
	forwardDirection = node->getAbsolutePosition() - temp;
	forwardDirection.normalize();

	// Initially setting IDLE animation.
	setIdleAnimation();

	// Calculating cameraDistance.
	temp = node->getAbsolutePosition() - (camera->getNode()->getAbsolutePosition());
	cameraDistance = abs(temp.getLength());
}

void Player::takeDamage(u8 attackRating)
{
	// Reduce Player Health.
	health -= attackRating * 10;
}

void Player::takePickup()
{
	health += PICKUP_HEAL;
	if (health > 100)
	{
		health = 100;
	}
}

void Player::kill()
{
	health = 0;
}

bool Player::isDead()
{
	return (health <= 0);
}

u8 Player::getHealth()
{
	return health;
}

u8 Player::getMana()
{
	return mana;
}

void Player::incrementMana()
{
	mana += MANA_REGENERATE_PER_SEC;
	if (mana > 100)
	{
		mana = 100;
	}
}

IAnimatedMesh* Player::getMesh()
{
	return mesh;
}

IAnimatedMeshSceneNode* Player::getNode()
{
	return node;
}

vector3df Player::getPosition()
{
	node->updateAbsolutePosition();
	return node->getAbsolutePosition();
}

vector3df Player::getDirection()
{
	return forwardDirection;
}

void Player::moveForward(f32 deltaTime)
{
	node->updateAbsolutePosition();
	node->setPosition(node->getAbsolutePosition() + (forwardDirection * speed * deltaTime));
	
	node->updateAbsolutePosition();
	forwardDirection.normalize();
	camera->getNode()->setPosition((-1.0f * forwardDirection * cameraDistance) + node->getAbsolutePosition());
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setPosition(vector3df(camera->getNode()->getAbsolutePosition().X, camera->getNode()->getAbsolutePosition().Y + 50, camera->getNode()->getAbsolutePosition().Z));
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setTarget(node->getAbsolutePosition());
}

void Player::moveBackward(f32 deltaTime)
{
	node->updateAbsolutePosition();
	node->setPosition(node->getAbsolutePosition() + (-1 * forwardDirection * speed * deltaTime));

	node->updateAbsolutePosition();
	forwardDirection.normalize();
	camera->getNode()->setPosition((-1.0f * forwardDirection * cameraDistance) + node->getAbsolutePosition());
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setPosition(vector3df(camera->getNode()->getAbsolutePosition().X, camera->getNode()->getAbsolutePosition().Y + 50, camera->getNode()->getAbsolutePosition().Z));
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setTarget(node->getAbsolutePosition());
}

void Player::turnLeft(f32 deltaTime)
{
	node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y - (0.1f * deltaTime), node->getRotation().Z));
	vector3df rotation = vector3df(0.0f, (-0.1f * deltaTime), 0.0f);
	forwardDirection = rotation.rotationToDirection(forwardDirection);
	forwardDirection.normalize();

	node->updateAbsolutePosition();
	camera->getNode()->setPosition((-1.0f * forwardDirection * cameraDistance) + node->getAbsolutePosition());
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setPosition(vector3df(camera->getNode()->getAbsolutePosition().X, camera->getNode()->getAbsolutePosition().Y + 50, camera->getNode()->getAbsolutePosition().Z));
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setTarget(node->getAbsolutePosition());
}

void Player::turnRight(f32 deltaTime)
{
	node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y + (0.1f * deltaTime), node->getRotation().Z));
	vector3df rotation = vector3df(0.0f, (0.1f * deltaTime), 0.0f);
	forwardDirection = rotation.rotationToDirection(forwardDirection);
	forwardDirection.normalize();
	
	node->updateAbsolutePosition();
	camera->getNode()->setPosition((-1.0f * forwardDirection * cameraDistance) + node->getAbsolutePosition());
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setPosition(vector3df(camera->getNode()->getAbsolutePosition().X, camera->getNode()->getAbsolutePosition().Y + 50, camera->getNode()->getAbsolutePosition().Z));
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setTarget(node->getAbsolutePosition());
}

void Player::strafeLeft(f32 deltaTime)
{
	vector3df normal = vector3df(0, 1, 0).crossProduct(forwardDirection);
	normal.normalize();

	node->updateAbsolutePosition();
	camera->getNode()->updateAbsolutePosition();

	node->setPosition(node->getAbsolutePosition() + (2.0f * speed * normal * deltaTime));
	camera->getNode()->setPosition(camera->getNode()->getAbsolutePosition() + (2.0f * normal * speed * deltaTime));

	node->updateAbsolutePosition();
	camera->getNode()->updateAbsolutePosition();

	camera->getNode()->setTarget(node->getAbsolutePosition());
}

void Player::strafeRight(f32 deltaTime)
{
	vector3df normal = forwardDirection.crossProduct(vector3df(0, 1, 0));
	normal.normalize();

	node->updateAbsolutePosition();
	camera->getNode()->updateAbsolutePosition();

	node->setPosition(node->getAbsolutePosition() + (speed * normal * 2.0f * deltaTime));
	camera->getNode()->setPosition(camera->getNode()->getAbsolutePosition() + (normal * speed * 2.0f * deltaTime));

	node->updateAbsolutePosition();
	camera->getNode()->updateAbsolutePosition();

	camera->getNode()->setTarget(node->getAbsolutePosition());
}

PowerBall* Player::Attack()
{
	if ((device->getTimer()->getTime() - lastAttack) < 2000.0f || mana < POWERBALL_COST)
	{
		return nullptr;
	}

	vector3df direction = forwardDirection;
	direction.Y = 0;
	direction.normalize();

	PowerBall* powerBall = new PowerBall(smgr, driver, node->getAbsolutePosition(), direction, 1.0f);
	lastAttack = device->getTimer()->getTime();
	mana -= 20;
	return powerBall;
}

bool Player::push()
{
	if ((device->getTimer()->getTime() - lastPush) > 3000.0f && mana >= PUSH_COST)
	{
		mana -= PUSH_COST;
		lastPush = device->getTimer()->getTime();
		return true;
	}
	return false;
}

void Player::teleport()
{
	if ((device->getTimer()->getTime() - lastTeleport) > 5000.0f && mana >= TELEPORT_COST)
	{
		mana -= TELEPORT_COST;
		lastTeleport = device->getTimer()->getTime();

		node->updateAbsolutePosition();
		camera->getNode()->updateAbsolutePosition();
		forwardDirection.normalize();

		node->setPosition(node->getAbsolutePosition() + (forwardDirection * 500.0f));
		camera->getNode()->setPosition(camera->getNode()->getAbsolutePosition() + (forwardDirection * 500.0f));

		node->updateAbsolutePosition();
		camera->getNode()->updateAbsolutePosition();

		camera->getNode()->setTarget(node->getAbsolutePosition());
	}
}

void Player::setIdleAnimation()
{
	if (state != State::IDLE)
	{
		node->setMD2Animation(EMAT_STAND);
		node->setAnimationSpeed(30);
		state = State::IDLE;
	}
}

void Player::setRunningAnimation()
{
	if (state != State::RUNNING)
	{
		node->setMD2Animation(EMAT_RUN);
		node->setAnimationSpeed(30);
		state = State::RUNNING;
	}
}

void Player::setAttackAnimation()
{
	node->setMD2Animation(EMAT_ATTACK);
	node->setAnimationSpeed(20);
	state = State::ATTACK;
}