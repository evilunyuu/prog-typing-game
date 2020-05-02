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

	_renderer = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(
					_window.get(),
					-1,
					SDL_RENDERER_ACCELERATED),
			SDL_DestroyRenderer);
	if (_renderer == nullptr)
		throw std::runtime_error("SDL_CreateRenderer failed!");
}

void Window::main_loop()
{
	SDL_Event event;
	const Uint8 * keys = SDL_GetKeyboardState(nullptr);

	// Main loop
	for (;;) {
		// Handle all events
		while (SDL_PollEvent(&event) > 0) {
			if (event.type == SDL_QUIT) return; // TODO: Add a confirmation?
			handle_event(event);
		}

		handle_keys(keys);

		process_logic();

		render_frame();
		SDL_RenderPresent( _renderer.get() );
	}
}
