#pragma once

#include "libs.h"
#include "Screen.h"
#include "Bullet.h"
#include "HumanPlayer.h"

class GameScreen : public Screen {
public:
	GameScreen();

	HumanPlayer* p;
	Player* tst;

	virtual void loop(const sf::Time& dt);
	virtual void handle(const sf::Event& ev);

private:
	virtual void draw (
			sf::RenderTarget& target,
			sf::RenderStates states) const;
};
