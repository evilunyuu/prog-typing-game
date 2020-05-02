/*
 * GameWindow.h
 *
 *  Created on: 2 мая 2020 г.
 *      Author: unyuu
 */

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include "Window.h"

class GameWindow: public Window
{
private:
	static constexpr int DEFAULT_WIDTH = 1280;
	static constexpr int DEFAULT_HEIGHT = 800;

	GameWindow(): Window(DEFAULT_WIDTH, DEFAULT_HEIGHT) {}
public:
	GameWindow(const GameWindow &) = delete;
	virtual ~GameWindow() = default;

	virtual void handle_event(const SDL_Event & event);
	virtual void handle_keys(const Uint8 * keys);
	virtual void process_logic();
	virtual void render_frame();


	static std::shared_ptr<GameWindow> create() {
		struct GameWindowInstantiator: public GameWindow {};
		return std::make_shared<GameWindowInstantiator>();
	}
};




#endif /* GAMEWINDOW_H_ */
