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
	static constexpr int DEFAULT_WIDTH = 1280;
	static constexpr int DEFAULT_HEIGHT = 800;
protected:
	std::shared_ptr<SDL_Window> _window { nullptr };
	int _width { 0 };
	int _height { 0 };

public:
	[[deprecated("Don't call this constructor directly!")]]
	Window(int width, int height);
	virtual ~Window() = default;

	static std::shared_ptr<Window> create(
			int width = DEFAULT_WIDTH,
			int height = DEFAULT_HEIGHT);
};



#endif /* WINDOW_H_ */
