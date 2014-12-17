#include "Monster.h"

Monster::Monster(vector3df newPosition, f32 newSpeed, ISceneManager* manager, Player* enemyTarget, IrrlichtDevice* irrDevice) : Enemy(newPosition, newSpeed, manager, enemyTarget)
{
	device = irrDevice;
	lastAttack = 0;
}

void Monster::update(f32 deltaTime)
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
				node->setPosition(node->getAbsolutePosition() + (direction * speed * 20.0f * deltaTime));
			}
		}

		return;
	}
	if (bNeedsUpdate)
	{
		if ((node->getAbsolutePosition() - target->getNode()->getAbsolutePosition()).getLength() < 70.0f)
		{
			attack();
		}
		else
		{
			run(deltaTime);
		}
	}
}

void Monster::attack()
{
	if (currentState != ENEMY_ATTACK)
	{
		currentState = ENEMY_ATTACK;
		node->setMD2Animation(EMAT_ATTACK);
	}

	if ((device->getTimer()->getTime() - lastAttack) > 3000.0f)
	{
		target->takeDamage(MONSTER_ATTACK);
		lastAttack = device->getTimer()->getTime();
	}
}

void Monster::dodge(f32 deltaTime)
{
	// Monster has very little brain.
}

void Monster::run(f32 deltaTime)
{
	if (currentState != ENEMY_RUN)
	{
		currentState = ENEMY_RUN;
		node->setMD2Animation(EMAT_RUN);
		node->setAnimationSpeed(20);
	}
	node->updateAbsolutePosition();
	target->getNode()->updateAbsolutePosition();
	vector3df direction = target->getPosition() - node->getAbsolutePosition();
	direction.normalize();
	node->setPosition(node->getAbsolutePosition() + (direction * speed * deltaTime));
	node->updateAbsolutePosition();
	facePlayer();
	node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y - 90, node->getRotation().Z));
}

void Monster::loadModel(IAnimatedMesh* mesh, ITexture* texture)
{
	node = smgr->addAnimatedMeshSceneNode(mesh);
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture(0, texture);
	node->setPosition(origPosition);
	node->addShadowVolumeSceneNode();

	// Make enemy away from the screen.
	node->setRotation(vector3df(0.0f, -90.0f, 0.0f));
	facingDirection = vector3df(0.0f, 0.0f, 1.0f);
	facingDirection.normalize();
}