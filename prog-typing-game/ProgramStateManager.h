/*
 * ProgramStateManager.h
 *
 *  Created on: 2 мая 2020 г.
 *      Author: unyuu
 */

#ifndef PROGRAMSTATEMANAGER_H_
#define PROGRAMSTATEMANAGER_H_

#include <memory>
#include <map>
#include <stack>
#include <stdexcept>

#include <SDL2/SDL.h>

#include "Window.h"

class ProgramStateHandler
{
public:
	using Ptr = std::shared_ptr<ProgramStateHandler>;

protected:
	Window::Ptr _window;
	bool _init_done { false };

public:
	ProgramStateHandler() = delete;
	ProgramStateHandler(const ProgramStateHandler &) = delete;
	ProgramStateHandler(Window::Ptr window);

	virtual ~ProgramStateHandler() = default;

	// "Is a state initialised" getter
	bool init_done() const { return _init_done; }

	// State transition methods
	virtual void state_init() { _init_done = true; }
	virtual void state_fini() { _init_done = false; }
	virtual void state_enter() {}
	virtual void state_leave() {}

	// Handling methods
	virtual void handle_event(const SDL_Event & event) = 0;
	virtual void handle_keys(const Uint8 * keys) = 0;
	virtual void process_logic() = 0;
	virtual void render_frame() = 0;
};

class ProgramStateManager
{
public:
	using Ptr = std::shared_ptr<ProgramStateManager>;
private:
	static Ptr s_instance;

	std::map<unsigned, ProgramStateHandler::Ptr> _handlers;
	unsigned _next_sid { 1 };

	std::stack<unsigned> _states;

	ProgramStateManager() = default;
public:
	ProgramStateManager(const ProgramStateManager &) = delete;
	~ProgramStateManager();

	static void init();
	static Ptr instance();

	// State handler
	ProgramStateHandler::Ptr handler(unsigned sid);
	
	// State handler creation
	template <typename T, typename... Args>
	unsigned create(Args&&... args) {
		static_assert(std::is_base_of<ProgramStateHandler, T>());
		unsigned sid = _next_sid++;
		_handlers[sid] = std::make_shared<T>(std::forward<Args...>(args)...);
		return sid;
	}

	// State handler addition
	unsigned add_handler(ProgramStateHandler::Ptr handler) {
		if (handler == nullptr)
			throw std::runtime_error(
					"An attempt was made to add a "
					"nullptr as a state handler!");
		unsigned sid = _next_sid++;
		_handlers[sid] = handler;
		return sid;
	}

	inline bool empty() const { return _states.empty(); }

	// Current state id getter (0 = no state)
	inline unsigned current_state() const {
		if (empty) return 0;
		return _states.top();
	}

	void push_state(unsigned state);
	void pop_state();
	void replace_state(unsigned state);
};


#endif /* PROGRAMSTATEMANAGER_H_ */
