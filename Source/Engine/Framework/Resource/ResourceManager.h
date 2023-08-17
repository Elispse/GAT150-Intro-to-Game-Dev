#pragma once
#include <map>
#include <string>
#include <memory>
#include "Framework/Singleton.h"
#include "Resource.h"

#define GET_RESOURCE(type, filename, ...) Jackster::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__)

namespace Jackster
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:

		template <typename T, typename ... TArgs>
		std::shared_ptr<T>Get(const std::string& filename, TArgs ... args);

	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resources;

	};

	template<typename T, typename ...TArgs>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		if (m_resources.find(filename) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T>(m_resources[filename]);
		}

		std::shared_ptr<T> resource = std::make_shared<T>();
		resource->Create(filename, args...);

		m_resources[filename] = resource;

		return resource;
	}
}