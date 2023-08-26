#include "Actor.h"
#include "Component/RenderComponent.h"

namespace Jackster
{
	CLASS_DEFINITION(Actor)

		Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;

		for (auto& component : other.components)
		{
			auto cloneComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			addComponent(std::move(cloneComponent));
		}
	}

	bool Actor::Initialize()
	{
		for (auto& Component : components)
		{
			Component->Initialize();
		}

		return false;
	}
	void Actor::OnDestroy()
	{
		for (auto& Component : components)
		{
			Component->OnDestroy();
		}
	}
	void Actor::Update(float dt)
	{
		if (lifespan != -1.0f)
		{
			lifespan -= dt;
			destroyed = (lifespan <= 0);
		}
		for (auto& Component : components)
		{
			Component->Update(dt);
		}
	}

	void Actor::Draw(Jackster::Renderer& renderer)
	{
		//if (m_model) m_model->Draw(renderer, m_transform);
		for (auto& component : components)
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
		components.push_back(std::move(component));
	}

	void Actor::Read(const json_t& value)
	{
		//GET_DATA(value, transform)) transform.Read(GET_DATA(value, transform));

		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);

		if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform));

		if (HAS_DATA(value, component) && GET_DATA(value, component).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, component).GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);

				addComponent(std::move(component));
			}
		}
	}
}