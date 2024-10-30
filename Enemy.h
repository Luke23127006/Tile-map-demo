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

	sf::Vector2f lastPosition;

	bool onGround;

	bool isDead;
	float deadTimer;
	
	void initVariables();
	void initHitbox();
public:
	Enemy();
	Enemy(float posX, float posY);
	virtual ~Enemy();
	
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	void setPosition(const float x, const float y);
	void setOnGround(bool onGround);

	void move(float dirX, float dirY, float deltaTime);
	void turnBack();
	void dead();
	const bool canDisapper() const;
	const bool getIsDead() const;

	void update(float deltaTime);
	void updateCollisionWithTile(sf::FloatRect tileBounds);
	void updateLastPosition();

	void render(sf::RenderTarget* target) const;
};

