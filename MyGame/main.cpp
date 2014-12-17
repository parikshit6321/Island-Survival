#include "Game.h"

// Entry point.
int main()
{
	// Initializing the engine.
	IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480), 32U, false, true);
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	// Making instance of our game.
	Game app;

	// Instantiating game objects.
	Terrain* terrain = new Terrain(smgr, driver);
	Camera* camera = new Camera(smgr);
	Player* player = new Player(device, smgr, driver, camera);
	Skybox* skybox = new Skybox(smgr, driver);
	smgr->setShadowColor();

	// Setup gameHud.
	GameHud* gameHud = new GameHud(device, smgr, driver);
	GameState gameState = GameState::MAIN_MENU;

	// Instantiating EventReciever instance.
	SAppContext context = SAppContext(device, &gameState);
	EventReciever* reciever = new EventReciever(context);
	device->setEventReceiver(reciever);

	// Adding collision detector for the terrain.
	ITriangleSelector* selector = smgr->createTerrainTriangleSelector(terrain->getNode());
	terrain->getNode()->setTriangleSelector(selector);

	const aabbox3d<f32> & box = player->getNode()->getBoundingBox();
	vector3df radius = box.MaxEdge - box.getCenter();

	if (selector)
	{
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(selector, player->getNode(), radius);
		player->getNode()->addAnimator(anim);
	}

	bool bPressed = false;
	u32 lastPress = 0;

	f32 deltaTime = 0.0f;
	f32 previousTime = 0.0f, presentTime = 0.0f;

	#ifdef DEBUG
		f32 previous = 0.0f;
		f32 now = 0.0f;
	#endif

	// Main game loop.
	while (device->run())
	{
		if (!device->isWindowActive())
		{
			device->yield();
			continue;
		}
		// Ensuring frame independant update.
		presentTime = device->getTimer()->getTime();
		deltaTime = presentTime - previousTime;

		// To pause/unpause the game.
		if (reciever->isKeyDown(KEY_KEY_P) && (device->getTimer()->getTime() - lastPress) > 2000)
		{
			app.gamePaused = !(app.gamePaused);

			#ifdef DEBUG
				std::cout << "\ngamePaused = " << std::boolalpha << app.gamePaused << std::endl;
			#endif

			lastPress = device->getTimer()->getTime();
		}

		// Maintaining FPS around 60
		if (deltaTime > 16 && !app.gamePaused)
		{
			previousTime = presentTime;
			driver->beginScene(true, true, SColor(255, 255, 255, 255));

			// Checking Game State.
			app.handleGameState(gameState, player, device, smgr, driver);

			// Function to handle user input.
			app.processInput(device, smgr, driver, selector, reciever, player, camera, deltaTime);

			// Update Player's Mana.
			if ((device->getTimer()->getTime() - app.getLastUpdate()) > 1000.0f)
			{
				player->incrementMana();
				app.setLastUpdate(device->getTimer()->getTime());
			}

			// Updating position of all GameObjects.
			app.updateGameObjects(deltaTime);

			// Handle collisions between faerie and powerballs.
			app.handleCollisions(player, camera, deltaTime);

			if (gameState != MAIN_MENU && gameState != GAME_COMPLETE && gameState != GAME_OVER)
			{
				// Render everything.
				smgr->drawAll();

				// Update Game Hud.
				gameHud->displayHealthBar(player->getHealth());
				gameHud->displayManaBar(player->getMana());
			}
			else
			{
				// Display the GUI.
				guienv->drawAll();
			}

			driver->endScene();

			#ifdef DEBUG
				now = device->getTimer()->getTime();
				if ((now - previous) > 5000.0f)
				{
					//std::cout << "\nDelta Time = " << deltaTime << std::endl;
					//std::cout << "FPS = " << (1000.0f / deltaTime) << "\n\n";
					//std::cout << "Player position = " << player->getPosition().X << ", " << player->getPosition().Y << ", " << player->getPosition().Z << std::endl;
					std::cout << "Number of Enemies = " << (int)app.getNumOfEnemies() << std::endl;
					previous = now;
				}
			#endif
		}
	}
}