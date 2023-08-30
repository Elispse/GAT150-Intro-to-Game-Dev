#pragma once
#include "Framework/Actor.h"
#include "Framework/Component/Physics.h"

namespace Jackster
{
	class Player : public Jackster::Actor
	{
	public:
		CLASS_DECLARATION(Player)

		bool Initialize() override;
		void Update(float dt) override;

		void onCollisionEnter(Actor* actor) override;

		bool pu_doubleShot = false;

	private:
		float m_speed = 0;
		float m_turnRate = 0;

		Jackster::Physics* m_physicsComponent = nullptr;
	};
}