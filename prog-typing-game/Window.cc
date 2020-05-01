/*
 * Window.cc
 *
 *  Created on: 2 мая 2020 г.
 *      Author: unyuu
 */

#include "Window.h"
#include <stdexcept>

Window::Window(int width, int height):
		_width(width), _height(height)
{
	_window = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
					"prog-typing-game",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					width, height,
					SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (_window == nullptr)
		throw std::runtime_error("SDL_CreateWindow failed!");
}

std::shared_ptr<Window> Window::create(int width, int height)
{
	return std::make_shared<Window>(width, height);
}
