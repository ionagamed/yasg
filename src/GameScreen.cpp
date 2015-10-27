#include "GameScreen.h"
#include "Bullet.h"
#include "Game.h"
#include "sfutil.h"

GameScreen::GameScreen() {
	sf::Color tmp = sf::Color::Blue;
	tmp.a = 128;

	p = new HumanPlayer(tmp);
	p->setPosition(400, 320);

	tmp = sf::Color::Red;
	tmp.a = 128;
	for (int i = 0; i < 20; i++) {
		tst.push_back(new Player(tmp));
		(*(tst.end() - 1))->setPosition(50 * i, 100);
	}

	shader.loadFromFile("data/shader/translate.vert", "data/shader/invert.frag");
	xLim = yLim = 0.0;
	xDecay = yDecay = 0.4;
}

double randomReal(double a, double b) {
	double p = (double) (rand() % 10000) / 10000.0;
	return a + p * (b - a);
}

const double EPS = 1e-4;
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
		pc->velocity = sf::rotate(pc->velocity, (float) (rand() % 265) / 420.0 - 132 / 420.0); if (pc->deadFrom(p)) {
			pc->setPosition(0xDEADC0DE, 0xDEADBEEF);
		}
	}

	shader.setParameter("invert", 0);

	double nx = randomReal(-xLim, xLim);
	shader.setParameter("ox", nx);
	if (nx > 2 * xLim / 3 || nx < -2 * xLim / 3) {
		shader.setParameter("invert", 1);
	}
	if (xLim < -EPS) {
		xLim += xDecay * dt.asSeconds();
	} else if (xLim > EPS) {
		xLim -= xDecay * dt.asSeconds();
	} else {
		xLim = 0.0;
	}

	double ny = randomReal(-yLim, yLim);
	shader.setParameter("oy", ny);
	if (ny > 2 * yLim / 3 || ny < -2 * yLim / 3) {
		shader.setParameter("invert", 1);
	}
	if (yLim < -EPS) {
		yLim += yDecay * dt.asSeconds();
	} else if (yLim > EPS) {
		yLim -= yDecay * dt.asSeconds();
	} else {
		yLim = 0.0;
	}

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
				case sf::Keyboard::Space:
					xLim = yLim = 0.2;
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
	states.shader = &shader;

	/// Used to do epic invert effect
	sf::RectangleShape s;
	s.setSize(sf::Vector2f(10000, 10000));
	s.setPosition(sf::Vector2f(-1000, -1000));
	s.setFillColor(sf::Color::White);
	target.draw(s, states);

	target.draw(*p, states);
	for (Player* ptr : tst) {
		target.draw(*ptr, states);
	}
}
