#include "BadFaerie.h"
#include <iostream>
#include <time.h>

BadFaerie::BadFaerie(vector3df position, f32 newSpeed, ISceneManager* manager, Player* playerTarget, IrrlichtDevice* irrDevice, list<GameObject*> * updateListPtr, IVideoDriver* videoDriver) : Enemy(position, newSpeed, manager, playerTarget)
{
	currentState = ENEMY_IDLE;
	driver = videoDriver;
	dodgeStart = 0;
	lastAttack = 0;
	device = irrDevice;
	listPtr = updateListPtr;
}

void BadFaerie::attack()
{
	if ((device->getTimer()->getTime() - lastAttack) < 1500.0f)
	{
		return;
	}

	target->getNode()->updateAbsolutePosition();
	node->updateAbsolutePosition();
	vector3df direction = target->getPosition() - node->getAbsolutePosition();
	direction.normalize();

	PowerBallEnemy* powerBall = new PowerBallEnemy(smgr, driver, node->getAbsolutePosition(), direction, 1.0f);
	lastAttack = device->getTimer()->getTime();

	listPtr->push_back(powerBall);
}

void BadFaerie::dodge(f32 deltaTime)
{
	if ((device->getTimer()->getTime() - dodgeStart) > 3000.0f)
	{
		currentState = ENEMY_IDLE;
		return;
	}
	
	vector3df direction = target->getPosition() - node->getAbsolutePosition();
	direction.normalize();

	vector3df normal = direction.crossProduct(vector3df(0, 1, 0));
	normal.normalize();

	node->setPosition(node->getAbsolutePosition() + (normal * speed * deltaTime));
}

void BadFaerie::run(f32 deltaTime)
{
	if (currentState != EnemyState::ENEMY_RUN)
	{
		currentState = EnemyState::ENEMY_RUN;
	}

	target->getNode()->updateAbsolutePosition();
	node->updateAbsolutePosition();

	facePlayer();
	node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y - 90, node->getRotation().Z));
	vector3df direction = target->getPosition() - node->getAbsolutePosition();
	direction.normalize();
	node->setPosition(node->getAbsolutePosition() + (direction * speed * deltaTime));
}

bool BadFaerie::listHasPowerBall()
{
	for each (GameObject* ptr in *listPtr)
	{
		if (dynamic_cast<PowerBall*>(ptr) != NULL)
		{
			return true;
		}
	}
	return false;
}

bool BadFaerie::seesPowerBall()
{
	srand(time(NULL));
	u8 chance = rand() % 2;

	if (((node->getAbsolutePosition() - target->getNode()->getAbsolutePosition()).getLength() > 100.0f) && chance == 0 && listHasPowerBall())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BadFaerie::update(f32 deltaTime)
{
	if (bPushedBack)
	{
		if ((device->getTimer()->getTime() - pushStart) > 3000.0f)
		{
			bPushedBack = false;
		}
		else
		{
			target->getNode()->updateAbsolutePosition();
			node->updateAbsolutePosition();

			facePlayer();
			node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y - 90, node->getRotation().Z));
			vector3df direction = target->getPosition() - node->getAbsolutePosition();

			if (direction.getLength() > 800.0f)
			{
				// Enemy is too far away.
			}
			else if (direction.dotProduct(target->getDirection()) > 0)
			{
				// Enemy is behind the player.
			}
			else
			{
				// Push the enemy.
				direction.Y = 0;
				direction *= -1.0f;
				direction.normalize();
				node->setPosition(node->getAbsolutePosition() + (deltaTime * direction * speed * 20.0f));
			}
		}

		return;
	}
	if (bNeedsUpdate)
	{
		if (currentState == ENEMY_DODGE)
		{
			dodge(deltaTime);
			return;
		}
		if (seesPowerBall())
		{
			currentState = ENEMY_DODGE;
			dodgeStart = device->getTimer()->getTime();
			dodge(deltaTime);
			return;
		}

		if ((node->getAbsolutePosition() - target->getNode()->getAbsolutePosition()).getLength() < 400.0f)
		{
			currentState = ENEMY_ATTACK;
			attack();
		}
		else
		{
			currentState = ENEMY_RUN;
			run(deltaTime);
		}
	}
}

void BadFaerie::loadModel(IAnimatedMesh* mesh, ITexture* texture)
{
	node = smgr->addAnimatedMeshSceneNode(mesh);
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture(0, texture);
	node->setPosition(origPosition);
	node->addShadowVolumeSceneNode();

	// Make enemy face towards the screen.
	node->setRotation(vector3df(0.0f, -90.0f, 0.0f));
	facingDirection = vector3df(0.0f, 0.0f, 1.0f);
	facingDirection.normalize();

	node->setMD2Animation(EMAT_STAND);
}