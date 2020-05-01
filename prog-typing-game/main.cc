#include <iostream>
#include <stdexcept>
#include <memory>

#include <SDL2/SDL.h>

#include "Window.h"

int main(int argc, char **argv)
{
	try {
		// SDL init
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw std::runtime_error("SDL_Init() failed!");

		// Window creation
		auto win = Window::create();



		// TODO: This delay is to be deleted later on
		SDL_Delay(2000);

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
