#pragma once

#include "Header.h"
#include "Camera.h"
#include "Player.h"
#include "Tile.h"
#include "Button.h"

extern Camera camera;

enum GameStates
{
	HOME_SCREEN = 0,
	SELECT_MAP,
	PLAYING,
};

extern GameStates gameState;
class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	float windowWidth;
	float windowHeight;
	bool resizing;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	Player* player;
	vector<vector<Tile> > tiles;
	vector<vector<bool> > map;
	Button* button;
	
	int currentMap;

	void initVariables();
	void initWindow();
	void initPlayer();
	void initTiles();
	void initMap();
	void initButton();
public:
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;


	// Functions
	void pollEvents();
	void updateMousePositions();

	// Update
	void update(float deltaTime);
	void updateCameraPosition(float deltaTime);
	void updateCollision();
	void updateMap();
	void updateButton(sf::Vector2f mousePosView);

	// Render
	void render();
	void renderMap();
	void renderButton();
};