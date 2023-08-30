#pragma once
#include "Collision.h"
#include "Physics/.vs/Physics/PhysicsSystem.h"
#include <functional>

namespace Jackster
{
	class Box2DCollisionComponent : public Collision
	{
	public:
		using collisionFunction = std::function<void(Actor*)>;

	public:
		CLASS_DECLARATION(Box2DCollisionComponent)

			virtual bool Initialize() override;
		virtual void Update(float dt) override;

	private:
		PhysicsSystem::CollisionData data;
		vec2 scaleOffset = vec2{ 1, 1 };
	};
}