#pragma once

#include "Header.h"

class Camera
{
private:
	float x, y;
public: 
	Camera(float x, float y, float zoomLevel = 1.f);
	const sf::View getView(sf::Vector2u windowSize);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);
	void move(float x, float y);
	void move(sf::Vector2f position);
	const sf::Vector2f getPosition() const;

	float zoomLevel;
};

