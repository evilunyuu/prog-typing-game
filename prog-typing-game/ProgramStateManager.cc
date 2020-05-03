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
	auto iter = _handlers.find(sid);
	if (iter == _handlers.end()) {
		std::stringstream ss;
		ss << "State handler with sid=" << sid << " not found!";
		throw std::runtime_error(ss.str());
	}
	return iter->second;
}


