#pragma once

#include "Player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer(sf::Color c) : Player(c) {};

	void loop(const sf::Time& dt);
};
