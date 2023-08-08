#include "Actor.h"
#include "Component/RenderComponent.h"

namespace Jackster
{
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}
		for (auto& Component : m_components)
		{
			Component->Update(dt);
		}
	}

	void Actor::Draw(Jackster::Renderer& renderer)
	{
		//if (m_model) m_model->Draw(renderer, m_transform);
		for (auto& component : m_components)
		{
			if (dynamic_cast<RenderComponent*>(component.get()))
			{
				dynamic_cast<RenderComponent*>(component.get())->Draw(renderer);
			}
		}
	}

	void Actor::addComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}

}
