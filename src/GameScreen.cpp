#include "GameScreen.h"
#include "Bullet.h"
#include "Game.h"
#include "sfutil.h"

GameScreen::GameScreen() {
	p = new HumanPlayer(sf::Color::Blue);
	p->setPosition(400, 320);
	for (int i = 0; i < 20; i++) {
		tst.push_back(new Player(sf::Color::Red));
		(*(tst.end() - 1))->setPosition(50 * i, 100);
	}

	Game::getInstance()->shader.loadFromFile("data/shader/translate.vert", "data/shader/alpha.frag");
}

#define PI 3.14159265358
void GameScreen::loop(const sf::Time& dt) {
	p->loop(dt);

	for (Player* pc : tst) {
		pc->loop(dt);
		sf::Vector2f towardsPlayer =
			sf::normalize(p->getPosition() - pc->getPosition());
		pc->spawnBullet (
				sf::rotate(towardsPlayer, (float) (rand() % 265) / 420.0 - 132 / 420.0)
				* (float) Bullet::speed / 3.0f);
		pc->velocity = towardsPlayer * (float) pc->speed / 4.0f;
		pc->velocity = sf::rotate(pc->velocity, (float) (rand() % 265) / 420.0 - 132 / 420.0);
		if (pc->deadFrom(p)) {
			pc->setPosition(0xDEADC0DE, 0xDEADBEEF);
		}
	}

	Game::getInstance()->shader.setParameter("ox", (float) (rand() % 265) / 7000.0 - 132 / 7000.0);
	Game::getInstance()->shader.setParameter("oy", (float) (rand() % 265) / 7000.0 - 132 / 7000.0);

	//if (p->deadFrom(tst)) {
		//p->setPosition(0xDEADC0DE, 0xDEADBEEF);
	//}
}

void GameScreen::handle(const sf::Event& ev) {
	switch (ev.type) {
		case sf::Event::KeyPressed:
			switch (ev.key.code) {
				case sf::Keyboard::R:
					p->setPosition(400, 320);
					break;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (ev.mouseButton.button == sf::Mouse::Right) {
				tst.push_back(new Player(sf::Color::Red));
				tst.back()->setPosition(
						ev.mouseButton.x,
						ev.mouseButton.y
						);
			}
			break;
	}
}

void GameScreen::draw (
		sf::RenderTarget& target,
		sf::RenderStates states) const {
	target.draw(*p, states);
	for (Player* ptr : tst) {
		target.draw(*ptr, states);
	}
}
