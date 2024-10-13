#include "Button.h"

Button::Button(string text, sf::Vector2f size, sf::Vector2f position)
{
	this->hitbox.setFillColor(this->normalColor);
	this->hitbox.setSize(size);
	this->hitbox.setPosition(position);

	this->font.loadFromFile("./resources/dosis.light.ttf");
	this->text.setFont(font);
	this->text.setString(text);
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color::Black);
	this->text.setPosition(
		position.x + (size.x - this->text.getGlobalBounds().width) / 2,
		position.y + (size.y - this->text.getGlobalBounds().height) / 2 - this->text.getGlobalBounds().top);
}

Button::~Button()
{
}

bool Button::isHovered(sf::Vector2f mousePosView)
{
	return this->hitbox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosView));
}

bool Button::isClicked(sf::Vector2f mousePosView)
{
	return (this->isHovered(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

void Button::update(sf::Vector2f mousePosView)
{
	if (this->isHovered(mousePosView)) this->hitbox.setFillColor(this->hoverColor);
	else this->hitbox.setFillColor(this->normalColor);
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->hitbox);
	target->draw(this->text);
}
