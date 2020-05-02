/*
 * ResourceManager.cc
 *
 *  Created on: 2 мая 2020 г.
 *      Author: unyuu
 */

#include "ResourceManager.h"

#include <stdexcept>
#include <sstream>

std::shared_ptr<ResourceManager> ResourceManager::s_instance { nullptr };

void ResourceManager::init()
{
	if (s_instance != nullptr)
		throw std::runtime_error(
				"The resource manager has already been initialized!");

	struct ResourceManagerInstantiator: public ResourceManager {};
	s_instance = std::make_shared<ResourceManagerInstantiator>();
}

ResourceManager::Ptr ResourceManager::instance()
{
	if (s_instance == nullptr) init();
	return s_instance;
}

// Resource getter
Resource::Ptr ResourceManager::resource(unsigned rid)
{
	auto iter = _resources.find(rid);
	if (iter == _resources.end()) {
		std::stringstream ss;
		ss << "Resource with rid=" << rid << " not found!";
		throw std::runtime_error(ss.str());
	}
	return iter->second;
}

// A DummyResource creation
unsigned ResourceManager::create_dummy_resource()
{
	unsigned rid = _next_rid++;
	_resources[rid] = std::make_shared<DummyResource>();
	return rid;
}


