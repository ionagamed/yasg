#pragma once

#include "libs.h"
#include "Bullet.h"

class Player : public sf::Transformable, public sf::Drawable {
public:
	sf::Vector2f velocity;
	std::list <Bullet> bullets;
	double speed;
	double cooldown;
	double lastShot;

	Player() {}
	Player(sf::Color c);

	void loop(const sf::Time& dt);
	virtual void spawnBullet(const sf::Vector2f& velo);
	virtual void resetBulletCooldown();

	/// WARNING: Linear algorithm
	/// Just goes through the bullets of p
	virtual bool deadFrom(const Player* p);

private:
	sf::CircleShape shape;

	virtual void draw (
			sf::RenderTarget& target,
			sf::RenderStates states) const;
};
