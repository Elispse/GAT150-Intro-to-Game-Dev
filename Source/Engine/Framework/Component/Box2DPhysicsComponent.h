#pragma once
#include "Physics.h"
#include <Physics/.vs/Physics/PhysicsSystem.h>

class b2Body;

namespace Jackster
{
	class Box2DPhysicsComponent : public Physics
	{
	public:
		CLASS_DECLARATION(Box2DPhysicsComponent)

		bool Initialize() override;
		void OnDestroy() override;

		void Update(float dt) override;

		virtual void ApplyForce(const vec2& force) override;
		virtual void ApplyTorque(float torque) override;

		virtual void SetPosition(const vec2& position) override;
		virtual void SetVelocity(const vec2& velocity) override;
		virtual void SetGravityScale(float scale) override;

		friend class Box2DCollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body = nullptr;
	};
}