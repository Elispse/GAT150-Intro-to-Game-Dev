#pragma once
#include "Physics.h"

namespace Jackster
{
	class EnginePhysicsComp : public Physics
	{
	public:
		// Inherited via Physics
		virtual void Update(float dt) override;

		virtual void ApplyForce(const vec2& force) override;

	};
}