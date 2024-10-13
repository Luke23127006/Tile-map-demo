#include "Tile.h"

Tile::Tile(float x, float y, float size)
{
	this->hitbox.setPosition(x, y);
	this->hitbox.setSize(sf::Vector2f(size, size));
	this->hitbox.setFillColor(sf::Color::Green);
	this->hitbox.setOutlineColor(sf::Color::Black);
	//this->hitbox.setOutlineThickness(1.f);
}

Tile::Tile()
{
	this->hitbox.setPosition(0.f, 0.f);
	this->hitbox.setSize(sf::Vector2f(50.f, 50.f));
	this->hitbox.setFillColor(sf::Color::Green);
	this->hitbox.setOutlineColor(sf::Color::Black);
}

Tile::~Tile()
{
}

const sf::Vector2f& Tile::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

void Tile::render(sf::RenderTarget* target)
{
	target->draw(this->hitbox);
}
