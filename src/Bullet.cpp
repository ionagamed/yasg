#include "Bullet.h"
#include "sfutil.h"

double Bullet::speed = 1000.0f;

Bullet::Bullet (
		sf::Vector2f position, 
		sf::Vector2f velocity, 
		sf::Color c) {
	this->velocity = velocity;
	setPosition(position);
	shape.setRadius(4.0);
	shape.setFillColor(c);
};

bool Bullet::stillAlive() {
	return
		getPosition().x >= 0.0 && getPosition().x <= 800.0 &&
		getPosition().y >= 0.0 && getPosition().y <= 640.0;
}

#define PI 3.14159265358
void Bullet::loop(const sf::Time& dt) {
	move(velocity * dt.asSeconds());
	//velocity = sf::rotate(velocity, PI * dt.asSeconds() * (float) (rand() % 265) / 420.0);
}

void Bullet::draw (
		sf::RenderTarget& target,
		sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(shape, states);
}
