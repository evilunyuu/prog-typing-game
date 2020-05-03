/*
 * ProgramStateManager.cc
 *
 *  Created on: 2 мая 2020 г.
 *      Author: unyuu
 */

#include "ProgramStateManager.h"

#include <stdexcept>
#include <sstream>

std::shared_ptr<ProgramStateManager>
ProgramStateManager::s_instance { nullptr };

ProgramStateManager::~ProgramStateManager()
{
	while (current_state() != 0) {
		pop_state();
	}
}

void ProgramStateManager::init()
{
	if (s_instance != nullptr)
		throw std::runtime_error(
				"The program state manager has already been initialised!");

	struct ProgramStateManagerInstantiator: public ProgramStateManager {};
	s_instance = std::make_shared<ProgramStateManagerInstantiator>();
}

ProgramStateManager::Ptr ProgramStateManager::instance()
{
	if (s_instance == nullptr) init();
	return s_instance;
}

ProgramStateHandler::Ptr ProgramStateManager::handler(unsigned sid)
{
	if (sid == 0)
		return nullptr; // TODO: Make it a "safe" way
	auto iter = _handlers.find(sid);
	if (iter == _handlers.end()) {
		std::stringstream ss;
		ss << "State handler with sid=" << sid << " not found!";
		throw std::runtime_error(ss.str());
	}
	return iter->second;
}

void ProgramStateManager::push_state(unsigned state)
{
	auto current_sid = current_state();
	auto current_handler = handler(current_sid);
	auto next_handler = handler(state);
	if (not next_handler->init_done())
		next_handler->state_init();
	_states.push(state);
	if (current_handler != nullptr)
		current_handler->state_leave();
	next_handler->state_enter();
}

void ProgramStateManager::pop_state()
{
	auto current_sid = current_state();
	auto current_handler = handler(current_sid);
	current_handler->state_leave();
	current_handler->state_fini();
	_states.pop();
	current_sid = current_state();
	current_handler = handler(current_sid);
	if (current_handler != nullptr)
		current_handler->state_enter();
}

void ProgramStateManager::replace_state(unsigned state)
{
	auto current_sid = current_state();
	auto current_handler = handler(current_sid);
	auto next_handler = handler(state);
	current_handler->state_leave();
	current_handler->state_fini();
	_states.pop();
	next_handler->state_init();
	_states.push(state);
	next_handler->state_enter();
}

