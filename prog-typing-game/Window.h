/*
 * Window.h
 *
 *  Created on: 2 мая 2020 г.
 *      Author: unyuu
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>
#include <memory>

class Window
{
public:
	using Ptr = std::shared_ptr<Window>;
	using RendererPtr = std::shared_ptr<SDL_Renderer>;
protected:
	std::shared_ptr<SDL_Window> _window { nullptr };
	std::shared_ptr<SDL_Renderer> _renderer { nullptr };
	int _width { 0 };
	int _height { 0 };

	Window(int width, int height);

public:
	Window(const Window &) = delete;
	virtual ~Window() = default;

	// Window width getter
	int width() const { return _width; }

	// Window height getter
	int height() const { return _height; }

	// Renderer getter
	RendererPtr renderer() { return _renderer; }

public:
	// Main loop routine
	void main_loop();

	virtual void handle_event(const SDL_Event & event) = 0;
	virtual void handle_keys(const Uint8 * keys) = 0;
	virtual void process_logic() = 0;
	virtual void render_frame() = 0;
};



#endif /* WINDOW_H_ */
