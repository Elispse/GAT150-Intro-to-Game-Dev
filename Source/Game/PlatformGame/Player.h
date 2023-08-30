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
		void onCollisionExit(Actor* actor) override;

		bool pu_doubleShot = false;

	private:
		float m_speed = 0;
		float maxSpeed = 0;
		float jump = 0;
		int groundCount = 0;

		Jackster::Physics* m_physicsComponent = nullptr;
	};
}