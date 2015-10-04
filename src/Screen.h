#pragma once

#include "libs.h"

class Screen : public sf::Drawable {
public:
	virtual void loop(const sf::Time& dt) = 0;
	virtual void handle(const sf::Event& ev) = 0;

private:
	virtual void draw (
			sf::RenderTarget& target,
			sf::RenderStates states) const = 0;
};
