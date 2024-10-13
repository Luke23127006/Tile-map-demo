#pragma once

#include "Header.h"

class Player
{
private:
	sf::RectangleShape hitbox;
	
	sf::Vector2f velocity;
	sf::Vector2f velocityMax;
	float acceleration;
	float accelerationMax;
	float deceleration;
	float gravity;
	float jumpHeight;

	bool onGround;
	sf::Vector2f lastPosition;

	void initVariables();
	void initHitbox();
public:
	Player();
	virtual ~Player();

	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getVelocity() const;

	void setPosition(const float x, const float y);
	void setOnGround(bool onGround);

	void move(const float dirX, const float dirY, float deltaTime);
	void update(float deltaTime);
	void updateMovement(float deltaTime);
	void updateCollisionWithWindow(sf::Vector2u windowSize);
	void updateCollisionWithTile(sf::FloatRect tileBounds);
	void updateLastPosition();

	void render(sf::RenderTarget* target);
};

