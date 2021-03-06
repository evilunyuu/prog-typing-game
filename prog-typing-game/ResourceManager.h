/*
 * ResourceManager.h
 *
 *  Created on: 2 мая 2020 г.
 *      Author: unyuu
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <memory>
#include <map>

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
public:
	using Ptr = std::shared_ptr<ResourceManager>;
private:
	static Ptr s_instance;

	std::map<unsigned, Resource::Ptr> _resources;
	unsigned _next_rid { 1 };

	ResourceManager() = default;
public:
	ResourceManager(const ResourceManager &) = delete;
	~ResourceManager() = default;

	static void init();
	static Ptr instance();

	// Resource getter
	Resource::Ptr resource(unsigned rid);

	// Resource creation
	template <typename T, typename... Args>
	unsigned create(Args&&... args) {
		static_assert(std::is_base_of<Resource, T>());
		unsigned rid = _next_rid++;
		_resources[rid] = std::make_shared<T>(std::forward<Args...>(args)...);
		return rid;
	}

};

#endif /* RESOURCEMANAGER_H_ */
