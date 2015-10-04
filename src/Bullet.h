#pragma once

#include "libs.h"

class Bullet : public sf::Drawable, public sf::Transformable {
public:
	Bullet (
			sf::Vector2f position,
			sf::Vector2f velocity, 
			sf::Color c);

	bool stillAlive();
	void loop(const sf::Time& dt);

	static double speed;

private:
	sf::Vector2f velocity;
	sf::CircleShape shape;

	virtual void draw (
			sf::RenderTarget& target,
			sf::RenderStates states) const;
};
