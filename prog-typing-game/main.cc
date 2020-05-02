#include <iostream>
#include <stdexcept>
#include <memory>

#include <map>
#include <sstream>

#include <SDL2/SDL.h>

#include "GameWindow.h"

class Resource
{
public:
	using Ptr = std::shared_ptr<Resource>;
};

class DummyResource: public Resource // for testing
{

};

class ResourceManager
{
private:
	static std::shared_ptr<ResourceManager> s_instance;

	std::map<unsigned, Resource::Ptr> _resources;
	unsigned _next_rid { 1 };

	ResourceManager() = default;
public:
	ResourceManager(const ResourceManager &) = delete;
	~ResourceManager() = default;

	using Ptr = std::shared_ptr<ResourceManager>;

	static void init();
	static Ptr instance();

	// A DummyResource creation
	unsigned create_dummy_resource() {
		unsigned rid = _next_rid++;
		_resources[rid] = std::make_shared<DummyResource>();
		return rid;
	}

	// Resource getter
	Resource::Ptr resource(unsigned rid) {
		auto iter = _resources.find(rid);
		if (iter == _resources.end()) {
			std::stringstream ss;
			ss << "Resource with rid=" << rid << " not found!";
			throw std::runtime_error(ss.str());
		}
		return iter->second;
	}
};

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

int main(int argc, char **argv)
{
	try {
		// SDL init
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw std::runtime_error("SDL_Init() failed!");

		// Window creation
		auto win = GameWindow::create();

		// Resource manager creation
		auto rm = ResourceManager::instance();
		auto dr1 = rm->create_dummy_resource();
		auto dr2 = rm->create_dummy_resource();

		std::cout << "Created a dummy resource dr1 = " << dr1 << std::endl;
		std::cout << "Created a dummy resource dr2 = " << dr2 << std::endl;

		std::cout << "dr1 is ";
		if (rm->resource(dr1) != nullptr)
			std::cout << "valid";
		else
			std::cout << "invalid";
		std::cout << std::endl;

		std::cout << "dr2 is ";
		if (rm->resource(dr2) != nullptr)
			std::cout << "valid";
		else
			std::cout << "invalid";
		std::cout << std::endl;

		std::cout << "resource with rid=0 is ";
		if (rm->resource(0) != nullptr)
			std::cout << "valid";
		else
			std::cout << "invalid";
		std::cout << std::endl;


		// Main loop
		win->main_loop();

	} catch (const std::exception& e) {
		std::cout <<
				"An exception has occured:" << std::endl <<
				e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cout <<
				"An unknown exception has occured!" << std::endl;
		return 2;
	}

	return 0;
}
