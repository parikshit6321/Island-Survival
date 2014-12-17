#include "Enemy.h"

Enemy::Enemy(vector3df newPosition, f32 newSpeed, ISceneManager* manager, Player* enemyTarget) : GameObject(newPosition, newSpeed, manager), target(enemyTarget)
{
	node = NULL;
	currentState = EnemyState::ENEMY_IDLE;
	bPushedBack = false;
}

void Enemy::update(f32 deltaTime)
{
}

void Enemy::loadModel(IAnimatedMesh* mesh, ITexture* texture)
{
}

ISceneNode* Enemy::getNode()
{
	return node;
}

vector3df Enemy::getPosition()
{
	node->updateAbsolutePosition();
	return node->getAbsolutePosition();
}

vector3df getTargetAngle(vector3df v, vector3df r)
{
	//v -current node position
	//r -target node position

	vector3df angle;
	float x, y, z;
	x = r.X - v.X;
	y = r.Y - v.Y;
	z = r.Z - v.Z;

	//angle in X-Z plane
	angle.Y = atan2(x, z);
	angle.Y *= (180 / PI); //converting from rad to degrees

	//just making sure angle is somewhere between 0-360 degrees
	if (angle.Y < 0) angle.Y += 360;
	if (angle.Y >= 360) angle.Y -= 360;

	//angle in Y-Z plane while Z and X axes are already rotated around Y
	float z1 = sqrt(x*x + z*z);

	angle.X = atan2(z1, y);
	angle.X *= (180 / PI); //converting from rad to degrees
	angle.X -= 90;

	//just making sure angle is somewhere between 0-360 degrees
	if (angle.X < 0) angle.X += 360;
	if (angle.X >= 360) angle.X -= 360;

	return angle;
}

void Enemy::facePlayer()
{
	node->updateAbsolutePosition();
	node->setRotation(getTargetAngle(node->getAbsolutePosition(), target->getPosition()));
}

void Enemy::pushBack()
{
	bPushedBack = true;
	pushStart = device->getTimer()->getTime();
}