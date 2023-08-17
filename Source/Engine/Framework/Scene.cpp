#include "Scene.h"
#include "Framework/Component/Collision.h"

namespace Jackster
{
	void Scene::Update(float dt)
	{
		//remove destroyed actors
		auto iter = m_actors.begin();

		while (iter != m_actors.end())
		{
			(*iter)->Update(dt);

			if (iter->get()->m_destroyed)
			{
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
		//check collisions
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++)
		{
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++)
			{
				Collision* collision1 = (*iter1)->getComponent<Collision>();
				Collision* collision2 = (*iter2)->getComponent<Collision>();

				if (!collision1 || !collision2) continue;

				if (collision1->collisionCheck(collision2))
				{
					(*iter1)->onCollision(iter2->get());
					(*iter2)->onCollision(iter1->get());
				}
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
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

	void Scene::RemoveAll()
	{
		m_actors.clear();
	}
	
}