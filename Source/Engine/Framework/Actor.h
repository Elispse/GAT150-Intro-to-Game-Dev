#pragma once
#include "Renderer/Model.h"
#include "Component/Components.h"
#include "Framework/Object.h"
#include <memory>

namespace Jackster
{
	class Actor : public Object
	{
		public:
			CLASS_DECLARATION(Actor)

			Actor() = default;
			Actor(const Jackster::Transform& transform) :
				m_transform{ transform }
			{}

			virtual bool Initialize() override;
			virtual void OnDestroy() override;

			virtual void Update(float dt);
			virtual void Draw(Renderer& renderer);

			void addComponent(std::unique_ptr<Component> component);
			template<typename T>
			T* getComponent();

			float getRadius() { return 30.0f; }
			virtual void onCollision(Actor* other) {};

			class Scene* m_scene = nullptr;
			friend class Scene;
			class Game* m_game = nullptr;

			Transform m_transform;
			std::string m_tag;
			float m_lifespan = -1.0f;

		protected:
			std::vector<std::unique_ptr<class Component>> m_components;
			bool m_destroyed = false;
		};

		template<typename T>
		inline T* Actor::getComponent()
		{
			for (auto& component : m_components)
			{
				T* result = dynamic_cast<T*> (component.get());

				if (result)
					return result;
			}
			return nullptr;
		}
}

