#pragma once

#include "libs.h"

#include "Screen.h"

class Game {
public:
	static Game* getInstance();

	sf::RenderWindow* window;
	Screen* screen;

	void init();
	int run();
	void exit();

	/// Executes the job out of main game loop
	//
	/// Used mainly to change screens 
	/// (so we won't break the pointer and context)
	void outOfLoop(Procedure job);

private:
	std::queue <Procedure> jobs;
};
