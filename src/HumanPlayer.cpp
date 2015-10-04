#include "HumanPlayer.h"
#include "Game.h"
#include "sfutil.h"

void HumanPlayer::loop(const sf::Time& dt) {
	Player::loop(dt);

	const double cooldown = .1;

	static double lastShot = cooldown;
	lastShot += dt.asSeconds();

	const sf::Vector2f mouse = (sf::Vector2f) 
		sf::Mouse::getPosition(*Game::getInstance()->window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lastShot >= cooldown) {
		spawnBullet(sf::normalize(mouse - getPosition()) * (float) Bullet::speed);
		lastShot = 0.0;
	}

	int buttons = 0;
	sf::Vector2f cm(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		cm.y -= 1.0;
		buttons++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		cm.y += 1.0;
		buttons++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		cm.x -= 1.0;
		buttons++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		cm.x += 1.0;
		buttons++;
	}
	if (buttons % 4 != 0) {
		cm = sf::normalize(cm);
		velocity = cm * (float) speed;
	}
}
