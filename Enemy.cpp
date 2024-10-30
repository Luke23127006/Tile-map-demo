#include "Enemy.h"

void Enemy::initVariables()
{
	this->acceleration = 0.f;
	this->accelerationMax = 800.f;
	this->deceleration = 1600.f;
	this->gravity = 2000.f;
	this->velocity = sf::Vector2f(200.f, 0.f);
	this->velocityMax = sf::Vector2f(400.f, 1200.f);

	this->isDead = false;
	this->deadTimer = 1.f;

	this->onGround = false;
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

void Enemy::setOnGround(bool onGround)
{
	this->onGround = onGround;
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

void Enemy::dead()
{
	this->isDead = true;
	this->hitbox.setSize(sf::Vector2f(50.f, 25.f));
	this->hitbox.setPosition(sf::Vector2f(this->hitbox.getPosition().x, this->hitbox.getPosition().y + 25.f));
}

const bool Enemy::canDisapper() const
{
	return this->deadTimer <= 0.f;
}

const bool Enemy::getIsDead() const
{
	return this->isDead;
}

void Enemy::update(float deltaTime)
{
	if (this->isDead)
	{
		this->deadTimer -= deltaTime;
	}
	else
	{
		if (!this->onGround) this->velocity.y += this->gravity * deltaTime;
		else this->velocity.y = 0.f;
		this->hitbox.move(this->velocity * deltaTime);
	}
}

void Enemy::updateCollisionWithTile(sf::FloatRect tileBounds)
{
	bool aboveTile = false;
	sf::FloatRect enemyBounds = this->hitbox.getGlobalBounds();

	if (this->lastPosition.x <= tileBounds.left && this->lastPosition.x + enemyBounds.width >= tileBounds.left ||
		this->lastPosition.x >= tileBounds.left && this->lastPosition.x <= tileBounds.left + tileBounds.width)
	{
		if (this->lastPosition.y + enemyBounds.height <= tileBounds.top)
			aboveTile = true;
	}

	if (enemyBounds.left <= tileBounds.left && enemyBounds.left + enemyBounds.width >= tileBounds.left ||
		enemyBounds.left >= tileBounds.left && enemyBounds.left <= tileBounds.left + tileBounds.width)
	{
		if (enemyBounds.top + enemyBounds.height == tileBounds.top)
			this->onGround = true;
	}

	if (!enemyBounds.intersects(tileBounds)) return;
	if (aboveTile)
	{
		this->hitbox.setPosition(this->hitbox.getPosition().x, tileBounds.top - this->hitbox.getSize().y);
		this->velocity.y = 0.f;
		this->onGround = true;
	}
	else
	{
		if (this->hitbox.getPosition().x <= tileBounds.left)
		{
			this->hitbox.setPosition(tileBounds.left - this->hitbox.getSize().x, this->hitbox.getPosition().y);
			this->turnBack();
		}
		else if (this->hitbox.getPosition().x > tileBounds.left)
		{
			this->hitbox.setPosition(tileBounds.left + tileBounds.width, this->hitbox.getPosition().y);
			this->turnBack();
		}
	}
}

void Enemy::updateLastPosition()
{
	this->lastPosition = this->hitbox.getPosition();
}

void Enemy::render(sf::RenderTarget* target) const
{
	target->draw(this->hitbox);
}
