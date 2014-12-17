#include "Wraith.h"
#include "PowerBallEnemy.h"
#include <time.h>

Wraith::Wraith(vector3df newPosition, f32 newSpeed, ISceneManager* manager, Player* playerTarget, IrrlichtDevice* irrDevice, list<GameObject*> * updateListPtr, IVideoDriver* videoDriver) : Enemy(newPosition, newSpeed, manager, playerTarget)
{
	driver = videoDriver;
	device = irrDevice;
	listPtr = updateListPtr;
	lastAttack = 0;
	lastTeleport = 0;
}

void Wraith::update(f32 deltaTime)
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
		srand(time(NULL));
		u8 chance = rand() % 3;

		if ((node->getAbsolutePosition() - target->getNode()->getAbsolutePosition()).getLength() < 500.0f && chance == 0)
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

void Wraith::attack()
{
	if ((device->getTimer()->getTime() - lastAttack) < 3000.0f)
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

void Wraith::dodge(f32 deltaTime)
{
	// Wraith doesn't dodge, it teleports.
}

void Wraith::run(f32 deltaTime)
{
	// Teleportation.
	if ((device->getTimer()->getTime() - lastTeleport) < 3000.0f)
	{
		return;
	}
	else
	{
		srand(time(NULL));

		bool bMatched;

		vector3df position = vector3df(0, 80, 0);

		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = listPtr->begin();

		srand(time(NULL));
		while (true)
		{
			bMatched = false;

			for (int i = 0; i < listPtr->getSize(); ++i)
			{
				if (tempIterator.operator==(it))
				{
					break;
				}

				ptr = dynamic_cast<Enemy*>(it.operator*());

				if (ptr != NULL)
				{
					if (ptr->getPosition() == position)
					{
						bMatched = true;
						break;
					}
				}

				if (tempIterator.operator==(it.operator++()))
				{
					break;
				}
			}

			if (!bMatched)
			{
				break;
			}

			position = vector3df(100 + (rand() % 900), 60, 100 + (rand() % 900));
		}
		
		node->setPosition(position);
		node->updateAbsolutePosition();
		lastTeleport = device->getTimer()->getTime();
		facePlayer();
		node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y - 90, node->getRotation().Z));
	}
}

void Wraith::loadModel(IAnimatedMesh* mesh, ITexture* texture)
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
}