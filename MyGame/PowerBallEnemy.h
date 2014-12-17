#pragma once

#include "PowerBall.h"

class PowerBallEnemy : public PowerBall
{
public:
	PowerBallEnemy(ISceneManager* smgr, IVideoDriver* driver, vector3df start, vector3df end, f32 speed);
};

