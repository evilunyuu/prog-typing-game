#include <iostream>
#include <stdexcept>
#include <memory>

#include <SDL2/SDL.h>

#include "GameWindow.h"

int main(int argc, char **argv)
{
	try {
		// SDL init
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw std::runtime_error("SDL_Init() failed!");

		// Window creation
		auto win = GameWindow::create();


		win->main_loop();

	} catch (const std::exception& e) {
		std::cout <<
				"An exception has occured:" << std::endl <<
				e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cout <<
				"An unknown exception has occured!" << std::endl;
		return 2;
	}

	return 0;
}
