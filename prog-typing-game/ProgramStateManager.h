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

#include <SDL2/SDL.h>

class ProgramStateHandler
{
public:
	using Ptr = std::shared_ptr<ProgramStateHandler>;
public:
	virtual ~ProgramStateHandler() = default;

	virtual void handle_event(const SDL_Event & event);

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

	ProgramStateManager() = default;
public:
	ProgramStateManager(const ProgramStateManager &) = delete;
	~ProgramStateManager() = default;

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
};


#endif /* PROGRAMSTATEMANAGER_H_ */
