#pragma once
#include "Framework/Actor.h"
#include "Framework/Component/Physics.h"

namespace Jackster
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

		bool Initialize() override;
		void OnDestroy() override;
		void Update(float dt) override;

		virtual void onCollisionEnter(Actor* actor) override;

	protected:
		float m_speed = 0;
		float m_turnRate = 0;

		float m_fireRate = 0;
		float m_fireTimer = 0;
		float m_health = 10.0f;

		Jackster::Physics* m_physicsComponent = nullptr;
	};
}