#include "Player.h"

void Player::initVariables()
{
	this->velocity = sf::Vector2f(0.f, 0.f);
	this->velocityMax = sf::Vector2f(400.f, 2000.f);
	this->acceleration = 0.f;
	this->accelerationMax = 1000.f;
	this->deceleration = 1400.f;
	this->gravity = 3000.f;
	this->jumpHeight = -1000.f;

	this->isDead = false;
	this->deadTimer = 0.5f;

	this->onGround = true;
}

void Player::initHitbox()
{
	this->hitbox.setSize(sf::Vector2f(30.f, 50.f));
	this->hitbox.setFillColor(sf::Color::Magenta);
	this->hitbox.setPosition(200.f, 200.f);
	this->lastPosition = this->hitbox.getPosition();
}

Player::Player()
{
	this->initVariables();
	this->initHitbox();
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::Vector2f Player::getVelocity() const
{
	return this->velocity;
}

void Player::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x, y);
}

void Player::setOnGround(bool onGround)
{
	this->onGround = onGround;
}

const bool Player::getIsDead() const
{
	return this->isDead;
}

void Player::move(const float dirX, const float dirY, float deltaTime)
{
	this->hitbox.move(sf::Vector2f(dirX, dirY) * deltaTime);
}

void Player::update(float deltaTime)
{
	this->updateMovement(deltaTime);
}

void Player::updateMovement(float deltaTime)
{
	this->acceleration = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->acceleration += -this->accelerationMax;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->acceleration += this->accelerationMax;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->onGround)
	{
		this->velocity.y = this->jumpHeight;
		this->onGround = false;
	}

	// update velocity.x
	if (this->acceleration > 0.f)
	{
		if (this->velocity.x < 0.f) this->velocity.x += this->deceleration * deltaTime;
		this->velocity.x = min(this->velocityMax.x, this->velocity.x + this->acceleration * deltaTime);
	}
	else if (this->acceleration < 0.f)
	{
		if (this->velocity.x > 0.f) this->velocity.x -= this->deceleration * deltaTime;
		this->velocity.x = max(-this->velocityMax.x, this->velocity.x + this->acceleration * deltaTime);
	}
	else
	{
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = max(0.f, this->velocity.x - this->deceleration * deltaTime);
		}
		else if (this->velocity.x < 0.f)
		{
			this->velocity.x = min(0.f, this->velocity.x + this->deceleration * deltaTime);
		}
	}

	// update velocity.y
	if (!this->onGround)
		this->velocity.y = min(this->velocityMax.y, this->velocity.y + this->gravity * deltaTime);
	else
		this->velocity.y = 0.f;

	this->hitbox.move(this->velocity * deltaTime);
}

void Player::updateCollisionWithWindow(sf::Vector2u windowSize)
{
	if (this->hitbox.getPosition().y > windowSize.y - this->hitbox.getSize().y)
	{
		this->hitbox.setPosition(this->hitbox.getPosition().x, windowSize.y - this->hitbox.getSize().y);
		this->velocity.y = 0.f;
		this->onGround = true;
	}
	else if (this->hitbox.getPosition().y == windowSize.y - this->hitbox.getSize().y)
	{
		this->onGround = true;
	}
}

void Player::updateCollisionWithTile(sf::FloatRect tileBounds)
{
	bool aboveTile = false;
	bool belowTile = false;
	sf::FloatRect playerBounds = this->hitbox.getGlobalBounds();

	if (this->lastPosition.x <= tileBounds.left && this->lastPosition.x + playerBounds.width >= tileBounds.left ||
		this->lastPosition.x >= tileBounds.left && this->lastPosition.x <= tileBounds.left + tileBounds.width)
	{
		if (this->lastPosition.y + playerBounds.height <= tileBounds.top)
			aboveTile = true;
		else if (this->lastPosition.y >= tileBounds.top + tileBounds.height)
			belowTile = true;
	}

	if (playerBounds.left <= tileBounds.left && playerBounds.left + playerBounds.width >= tileBounds.left ||
		playerBounds.left >= tileBounds.left && playerBounds.left <= tileBounds.left + tileBounds.width)
	{
		if (playerBounds.top + playerBounds.height == tileBounds.top)
			this->onGround = true;
	}

	if (playerBounds.intersects(tileBounds))
	{
		if (aboveTile)
		{
			this->hitbox.setPosition(this->hitbox.getPosition().x, tileBounds.top - this->hitbox.getSize().y);
			this->velocity.y = 0.f;
			this->onGround = true;
		}
		else if (belowTile)
		{
			this->hitbox.setPosition(this->hitbox.getPosition().x, tileBounds.top + tileBounds.height);
			this->velocity.y = 0.f;
		}
		else
		{
			if (this->hitbox.getPosition().x <= tileBounds.left)
			{
				this->hitbox.setPosition(tileBounds.left - this->hitbox.getSize().x, this->hitbox.getPosition().y);
				this->acceleration = 0.f;
				this->velocity.x = 0.f;
			}
			else if (this->hitbox.getPosition().x > tileBounds.left)
			{
				this->hitbox.setPosition(tileBounds.left + tileBounds.width, this->hitbox.getPosition().y);
				this->acceleration = 0.f;
				this->velocity.x = 0.f;
			}
		}
	}

	//cout << this->hitbox.getPosition().x << '\t' << this->hitbox.getPosition().y << '\n';
}

void Player::updateCollsionWithEnemy(sf::FloatRect enemyBounds)
{
	bool above = false;
	sf::FloatRect playerBounds = this->hitbox.getGlobalBounds();

	if (this->lastPosition.x <= enemyBounds.left && this->lastPosition.x + playerBounds.width > enemyBounds.left ||
		this->lastPosition.x > enemyBounds.left && this->lastPosition.x <= enemyBounds.left + enemyBounds.width)
	{
		if (this->lastPosition.y + this->getGlobalBounds().height < enemyBounds.top)
		above = true;
	}

	if (above)
	{
		this->hitbox.setPosition(this->hitbox.getPosition().x, enemyBounds.top - playerBounds.height);
		this->velocity.y = -800.f;
	}
	else
	{
		this->isDead = true;
		this->velocity.x = 0.f;
		this->velocity.y = -1000.f;
	}
}

void Player::updateLastPosition()
{
	this->lastPosition = this->hitbox.getPosition();
}

void Player::updateDeadAnimation(float deltaTime)
{
	//this->velocity.x = 0.f;
	this->deadTimer -= deltaTime;
	if (this->deadTimer > 0.f) return;
	this->velocity.y += this->gravity * deltaTime;
	this->move(0.f, this->velocity.y, deltaTime);
}

void Player::render(sf::RenderTarget* target) const
{
	//if (!this->isDead)
	target->draw(this->hitbox);
}
