#include "EnginePhysicsComp.h"
#include "FrameWork/Actor.h"

namespace Jackster
{
	CLASS_DEFINITION(EnginePhysicsComp)

	void EnginePhysicsComp::Update(float dt)
	{
		m_owner->transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void EnginePhysicsComp::ApplyForce(const vec2& force)
	{
		m_velocity += force;
	}

	void EnginePhysicsComp::ApplyTorque(float torque)
	{

	}

	void EnginePhysicsComp::Read(const json_t& value)
	{

	}
}