#include "GameScreen.h"
#include "Bullet.h"
#include "Game.h"
#include "sfutil.h"

GameScreen::GameScreen() {
	p = new HumanPlayer(sf::Color::Blue);
	p->setPosition(400, 320);
	tst = new Player(sf::Color::Red);
	tst->setPosition(100, 100);
}

void GameScreen::loop(const sf::Time& dt) {
	p->loop(dt);

	tst->loop(dt);
	tst->velocity = sf::Vector2f(30.0f, 30.0f);
	sf::Vector2f towardsPlayer = sf::normalize(p->getPosition() - tst->getPosition());
	towardsPlayer = sf::rotate(towardsPlayer, (float) (rand() % 265) / 420.0);
	tst->spawnBullet(towardsPlayer * (float) Bullet::speed / 3.0f);

	if (tst->deadFrom(p)) {
		tst->setPosition(0xDEADC0DE, 0xDEADBEEF);
	}
	if (p->deadFrom(tst)) {
		p->setPosition(0xDEADC0DE, 0xDEADBEEF);
	}
}

void GameScreen::handle(const sf::Event& ev) {

}

void GameScreen::draw (
		sf::RenderTarget& target,
		sf::RenderStates states) const {
	target.draw(*p, states);
	target.draw(*tst, states);
}
