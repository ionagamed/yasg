#include "Player.h"
#include "sfutil.h"

Player::Player(sf::Color c) {
	shape.setFillColor(c);
	shape.setRadius(16.0);
	shape.setOrigin(16.0, 16.0);

	speed = 300.0f;
	cooldown = 0.1f;
	lastShot = 2 * cooldown;

	velocity = sf::Vector2f(0, 0);
}

void Player::loop(const sf::Time& dt) {
	move(velocity * dt.asSeconds());
	velocity *= .5f;

	for (Bullet& b : bullets) {
		b.loop(dt);
	}
	
	auto bullet = bullets.begin();
	while (bullet != bullets.end()) {
		while (bullet != bullets.end() && !bullet->stillAlive()) {
			bullet = bullets.erase(bullet);
		}
		bullet++;
	}

	lastShot += dt.asSeconds();
}

void Player::spawnBullet(const sf::Vector2f& velo) {
	if (lastShot >= cooldown) {
		bullets.push_back(Bullet(
					getPosition(),
					sf::Vector2f(velo),
					shape.getFillColor()
					));
		lastShot = 0.0;
	}
}

void Player::resetBulletCooldown() {
	lastShot = cooldown + 1;
}

bool Player::deadFrom(const Player* p) {
	for (Bullet b : p->bullets) {
		if (sf::magnitude(getPosition() - b.getPosition()) < 20.0) {
			return true;
		}
	}
	return false;
}

void Player::draw (
		sf::RenderTarget& target,
		sf::RenderStates states) const {
	for (Bullet it : bullets) {
		target.draw(it, states);
	}
	states.transform *= getTransform();
	target.draw(shape, states);
}
