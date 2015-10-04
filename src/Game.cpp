#include "Game.h"
#include "GameScreen.h"

Game* Game::getInstance() {
	static Game* instance = NULL;
	if (instance == NULL) {
		return instance = new Game();
	}
	return instance;
}

void Game::init() {
	window = new sf::RenderWindow(
			sf::VideoMode(800, 640),
			"Yet Another Shooter Game"
	);
	window->setVerticalSyncEnabled(true);
	screen = new GameScreen();
}

int Game::run() {
	sf::Clock clock;
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				exit();
			} else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
				assert(false);
			} else {
				screen->handle(event);
			}
		}

		window->clear(sf::Color::White);
		screen->loop(clock.restart());
		window->draw(*screen);
		window->display();
	
		if (!jobs.empty()) {
			jobs.front()();
			jobs.pop();
		}
	}
	return 0;
}

void Game::exit() {
	outOfLoop([] {
			Game::getInstance()->window->close();
	});
}

void Game::outOfLoop(Procedure job) {
	jobs.push(job);
}

int main() {
	Game::getInstance()->init();
	return Game::getInstance()->run();
}
