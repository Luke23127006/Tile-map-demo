#include "Camera.h"

Camera::Camera(float x, float y, float zoomLevel)
{
	this->x = x;
	this->y = y;
	this->zoomLevel = zoomLevel;
}

const sf::View Camera::getView(sf::Vector2u windowSize)
{
	float aspect = float(windowSize.x) / float(windowSize.y);
	sf::Vector2f size;

	if (aspect > 1.f)
	{
		size = sf::Vector2f(zoomLevel * aspect, zoomLevel);
	}
	else
	{
		size = sf::Vector2f(zoomLevel, zoomLevel / aspect);
	}
	return sf::View(sf::Vector2f(this->x, this->y), size);
}

void Camera::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Camera::setPosition(sf::Vector2f position)
{
	this->x = position.x;
	this->y = position.y;
}

void Camera::move(float x, float y)
{
	this->x += x;
	this->y += y;
}

void Camera::move(sf::Vector2f position)
{
	this->x += position.x;
	this->y += position.y;
}

const sf::Vector2f Camera::getPosition() const
{
	return sf::Vector2f(this->x, this->y);
}
