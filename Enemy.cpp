#include "Enemy.h"

void Enemy::initVariables()
{
	this->acceleration = 0.f;
	this->accelerationMax = 800.f;
	this->deceleration = 1600.f;
	this->gravity = 2000.f;
	this->velocity = sf::Vector2f(100.f, 0.f);
	this->velocityMax = sf::Vector2f(400.f, 1200.f);
}

void Enemy::initHitbox()
{
	this->hitbox.setSize(sf::Vector2f(50.f, 50.f));
	this->hitbox.setFillColor(sf::Color(255, 127, 0, 255));
	this->hitbox.setPosition(0.f, 0.f);
}

Enemy::Enemy()
{
	this->initVariables();
	this->initHitbox();
}

Enemy::Enemy(float posX, float posY)
{
	this->initVariables();
	this->initHitbox();
	this->setPosition(posX, posY);
}

Enemy::~Enemy()
{
}

const sf::Vector2f& Enemy::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect Enemy::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

void Enemy::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x, y);
}

void Enemy::move(float dirX, float dirY, float deltaTime)
{
	this->velocity.x += dirX * this->acceleration * deltaTime;
	this->velocity.y += dirY * this->acceleration * deltaTime;
}

void Enemy::turnBack()
{
	this->velocity.x = -this->velocity.x;
}

void Enemy::update(float deltaTime)
{
	this->hitbox.move(this->velocity * deltaTime);
}

void Enemy::updateCollisionWithTile(sf::FloatRect tileBounds)
{
	sf::FloatRect eBounds = this->hitbox.getGlobalBounds();

	if (eBounds.left < tileBounds.left)
	{
		this->hitbox.setPosition(tileBounds.left - eBounds.width, eBounds.top);
	}
	else
	{
		this->hitbox.setPosition(tileBounds.left + tileBounds.width, eBounds.top);
	}

	this->turnBack();
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->hitbox);
}
