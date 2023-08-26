#pragma once
#include <list>
#include "Actor.h"


namespace Jackster 
{
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;

		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void Remove(Actor* actor);
		void RemoveAll(bool force = false);

		bool Load(const std::string& filename);
		void Read(const json_t& value);

		template<typename T>
		T* getActor();
		template<typename T = Actor>
		T* getActorByName(const std::string& name);

		friend class Actor;

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
	};

	template<typename T>
	inline T* Scene::getActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}
	template<typename T>
	inline T* Scene::getActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (actor->name == name)
			{
				T* result = dynamic_cast<T*>(actor.get());
				if (result) return result;
			}
		}

		return nullptr;
	}
}