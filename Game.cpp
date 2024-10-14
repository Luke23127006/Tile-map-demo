#include "Game.h"

Camera camera(0, 0, 1);
GameStates gameState = HOME_SCREEN;

void Game::initVariables()
{
	this->window = nullptr;
	this->windowWidth = 1280.f;
	this->windowHeight = 720.f;
	camera = Camera(this->windowWidth / 2, this->windowHeight / 2, min(this->windowWidth, this->windowHeight));
	this->resizing = false;

	this->currentMap = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(windowWidth, 720);
	this->window = new sf::RenderWindow(this->videoMode, "Tile Map");
}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(100.f, 100.f);
}

void Game::initTiles()
{
	for (int i = 0; i < 100; i++) tiles.push_back(vector<Tile>(100));

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			tiles[i][j] = Tile(i * 50.f, j * 50.f, 50.f);
		}
	}
}

void Game::initMap()
{
	map.clear();
	for (int i = 0; i < 100; i++) map.push_back(vector<bool>(100, false));
	// load map from map.png
	sf::Image mapImage;
	mapImage.loadFromFile("./resources/map.png");

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (mapImage.getPixel(i, j) == sf::Color::Black)
			{
				map[i][j] = true;
			}
			if (mapImage.getPixel(i, j) == sf::Color(237, 28, 36, 255))
			{
				this->player->setPosition(i * 50.f, j * 50.f);
			}
			if (mapImage.getPixel(i, j) == sf::Color(255, 127, 0, 255))
			{
				enemies.push_back(new Enemy(i * 50.f, j * 50.f));
			}
		}
	}
}

void Game::initButton()
{
	this->button = new Button("Play", sf::Vector2f(300, 200), sf::Vector2f(400, 400));
}

void Game::initEnemies()
{
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initTiles();
	this->initMap();
	this->initButton();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->button;

	for (auto& e : this->enemies)
	{
		delete this->enemies.at(0);
		this->enemies.erase(this->enemies.begin());
	}
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		this->resizing = false;
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				gameState = GameStates::HOME_SCREEN;
			break;
		case sf::Event::Resized:
			this->resizing = true;
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update(float deltaTime)
{
	this->pollEvents();
	this->updateMousePositions();

	if (this->resizing == true) return;

	switch (gameState)
	{
	case GameStates::HOME_SCREEN:
		this->updateButton(this->mousePosView);
		break;
	case GameStates::PLAYING:
		this->player->update(deltaTime);
		this->updateMap();
		this->updateCollision();
		this->updateCameraPosition(deltaTime);
		this->updateEnemies(deltaTime);
		break;
	}
}

void Game::updateCameraPosition(float deltaTime)
{
	sf::Vector2f playerPosition = this->player->getPosition();
	sf::Vector2f newPosition = sf::Vector2f(playerPosition.x + 0.1f * this->windowWidth, playerPosition.y);
	camera.setPosition(newPosition);
}

void Game::updateCollision()
{
	this->player->setOnGround(false);

	int iRange = this->player->getGlobalBounds().left / 50;
	int jRange = this->player->getGlobalBounds().top / 50;

	if (this->player->getVelocity().y >= 0)
	{
		for (int i = max(0, iRange - 1); i < min(100, iRange + 2); i++)
			for (int j = max(0, jRange - 1); j < min(100, jRange + 2); j++)
			{
				if (this->map[i][j])
				{
					sf::FloatRect tileBounds = this->tiles[i][j].getGlobalBounds();
					this->player->updateCollisionWithTile(tileBounds);
				}
			}
	}
	else
	{
		for (int i = max(0, iRange - 1); i < min(100, iRange + 2); i++)
			for (int j = min(99, jRange + 1); j >= max(0, jRange - 1); j--)
			{
				if (this->map[i][j])
				{
					sf::FloatRect tileBounds = this->tiles[i][j].getGlobalBounds();
					this->player->updateCollisionWithTile(tileBounds);
				}
			}
	}

	//this->player->updateCollisionWithWindow(this->window->getSize());
	this->player->updateLastPosition();

	//cout << player->getPosition().x << "\t" << player->getPosition().y << endl;
}

void Game::updateMap()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = this->mousePosView;
		int i = mousePos.x / 50;
		int j = mousePos.y / 50;
		if (i >= 0 && i < 100 && j >= 0 && j < 100 && !tiles[i][j].getGlobalBounds().intersects(this->player->getGlobalBounds()))
		{
			this->map[i][j] = true;
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2f mousePos = this->mousePosView;
		int i = mousePos.x / 50;
		int j = mousePos.y / 50;
		if (i >= 0 && i < 100 && j >= 0 && j < 100)
		{
			this->map[i][j] = false;
		}
	}
}

void Game::updateButton(sf::Vector2f mousePosView)
{
	this->button->update(mousePosView);
	if (this->button->isClicked(mousePosView))
	{
		gameState = GameStates::PLAYING;
		this->initPlayer();
		this->initTiles();
		this->initMap();
	}
}

void Game::updateEnemies(float deltaTime)
{
	for (auto& e : enemies)
		if (e) e->update(deltaTime);

	// collision and turn back
	for (auto& e : enemies)
	{
		int iRange = e->getPosition().x / 50;
		int jRange = e->getPosition().y / 50;

		for (int i = max(0, iRange - 1); i < min(100, iRange + 2); i++)
			for (int j = max(0, jRange - 1); j < min(100, jRange + 2); j++)
			{
				if (map[i][j] && e->getGlobalBounds().intersects(this->tiles[i][j].getGlobalBounds()))
				{
					e->updateCollisionWithTile(this->tiles[i][j].getGlobalBounds());
				}
			}
	}
}

void Game::render()
{
	this->window->clear(sf::Color::White);

	// Render Objects

	switch (gameState)
	{
	case GameStates::HOME_SCREEN:
		this->window->setView(this->window->getDefaultView());
		this->renderButton();
		break;
	case GameStates::PLAYING:
		this->window->setView(camera.getView(this->window->getSize()));
		this->player->render(this->window);
		this->renderMap();
		this->renderEnemies();
		break;
	}

	// End of rendering

	this->window->display();
}

void Game::renderMap()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (this->map[i][j])
			{
				this->tiles[i][j].render(this->window);
			}
		}
	}
}

void Game::renderButton()
{
	this->button->render(this->window);
}

void Game::renderEnemies()
{
	for (auto& e : enemies)
		if (e) e->render(this->window);
}
