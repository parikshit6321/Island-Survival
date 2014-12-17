#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;

enum GameState
{
	MAIN_MENU,
	WAVE_1,
	WAVE_2,
	WAVE_3,
	WAVE_4,
	WAVE_5,
	GAME_COMPLETE,
	GAME_OVER
};

struct SAppContext
{
	IrrlichtDevice* device;
	GameState * gameStatePtr;

	SAppContext(IrrlichtDevice* irrDevice, GameState * gameState)
	{
		device = irrDevice;
		gameStatePtr = gameState;
	}

	
};

enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_PLAY_BUTTON,
	GUI_ID_CONTROLS_BUTTON,
	GUI_ID_INSTRUCTIONS_BUTTON,
	GUI_ID_INSTRUCTIONS_BACK_BUTTON,
	GUI_ID_CONTROLS_BACK_BUTTON
};

#pragma once
class EventReciever : public IEventReceiver
{
private:
	bool keyDown[KEY_KEY_CODES_COUNT];
	SAppContext & context;

public:
	EventReciever(SAppContext & Context);
	virtual bool OnEvent(const SEvent& event);
	virtual bool isKeyDown(EKEY_CODE keyCode) const;
	virtual bool isKeyUp(EKEY_CODE keyCode) const;
};

