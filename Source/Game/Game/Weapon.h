#pragma once
#include "Framework/Actor.h"
#include "Framework/Component/Physics.h"
#include "Core/Json.h"

namespace Jackster
{
	class Weapon : public Jackster::Actor
	{
	public:

		CLASS_DECLARATION(Weapon)

		bool Initialize() override;
		void Update(float dt) override;

		virtual void onCollisionEnter(Actor* actor);

	private:
		float speed = 0.0f;
		Physics* m_physicsComponent = nullptr;
	};
}