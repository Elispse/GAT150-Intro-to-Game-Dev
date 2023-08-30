#include "Scene.h"
#include "Framework/Component/Collision.h"

namespace Jackster
{
	bool Scene::Initialize()
	{
		for (auto& actor : m_actors) actor->Initialize();

		return true;
	}

	void Scene::Update(float dt)
	{
		//remove destroyed actors
		auto iter = m_actors.begin();

		while (iter != m_actors.end())
		{

			if ((*iter)->active) (*iter)->Update(dt);

			if (iter->get()->destroyed)
			{
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			if (actor->active) actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::Remove(Actor* actor)
	{
		//m_actors.remove(actor);
	}

	void Scene::RemoveAll(bool force)
	{
		auto iter = m_actors.begin();

		while (iter != m_actors.end())
		{
			if (force || !(*iter)->persistent)
			{
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	bool Scene::Load(const std::string& filename)
	{
		rapidjson::Document document;
		if (!Json::Load(filename, document))
		{
			ERROR_LOG("Could not load scene file: " << filename);
			return true;
		}
		Read(document);

		return true;
	}

	void Scene::Read(const json_t& value)
	{
		if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
		{
			for (auto& actorValue : GET_DATA(value, actors).GetArray())
			{
				std::string type;
				READ_DATA(actorValue, type);

				auto actor = CREATE_CLASS_BASE(Actor, type);
				actor->Read(actorValue);

				if (actor->prototype)
				{
					std::string name = actor->name;
					Factory::Instance().RegisterPrototype(name, std::move(actor));
				}
				else
				{
					Add(std::move(actor));
				}
			}
		}
	}
	
}