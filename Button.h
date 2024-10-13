#pragma once

#include "Header.h"

class Button
{
private:
	sf::RectangleShape hitbox;
	sf::Text text;
	sf::Font font;

	sf::Color normalColor = sf::Color::Blue;
	sf::Color hoverColor = sf::Color(0, 183, 239, 255);
public:
	Button(string text, sf::Vector2f size, sf::Vector2f position);
	virtual ~Button();

	bool isHovered(sf::Vector2f mousePosView);
	bool isClicked(sf::Vector2f mousePosView);
	void update(sf::Vector2f mousePosView);

	void render(sf::RenderTarget* target);
};

