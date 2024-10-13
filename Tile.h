#pragma once

#include "Header.h"

class Tile
{
private:
	sf::RectangleShape hitbox;
	sf::Vector2f position;
	sf::Vector2f size;
public:
	Tile(float x, float y, float size = 50.f);
	Tile();
	virtual ~Tile();

	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	void render(sf::RenderTarget* target);
};

