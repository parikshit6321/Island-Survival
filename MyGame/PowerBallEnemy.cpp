#include "PowerBallEnemy.h"


PowerBallEnemy::PowerBallEnemy(ISceneManager* smgr, IVideoDriver* driver, vector3df start, vector3df end, f32 speed) : PowerBall(smgr, driver, start, end, speed)
{
	node->setMaterialTexture(0, driver->getTexture("Textures/powerballenemy.bmp"));
}