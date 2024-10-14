#pragma once

#include "Header.h"

class Enemy
{
private:
	sf::RectangleShape hitbox;

	sf::Vector2f velocity;
	sf::Vector2f velocityMax;
	float acceleration;
	float accelerationMax;
	float deceleration;
	float gravity;
	
	void initVariables();
	void initHitbox();
public:
	Enemy();
	Enemy(float posX, float posY);
	virtual ~Enemy();
	
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	void setPosition(const float x, const float y);

	void move(float dirX, float dirY, float deltaTime);
	void turnBack();

	void update(float deltaTime);
	void updateCollisionWithTile(sf::FloatRect tileBounds);

	void render(sf::RenderTarget* target);
};

