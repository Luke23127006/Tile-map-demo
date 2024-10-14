#include "Header.h"
#include "Game.h"

int main()
{
	srand(time(NULL));

	sf::Clock clock;

	Game* game = new Game();
	while (game->running())
	{
		float deltaTime = clock.restart().asSeconds();
		game->update(deltaTime);
		game->render();
	}
	delete game;

	return 0;
}