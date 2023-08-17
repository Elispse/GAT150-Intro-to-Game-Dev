#include "CircleCollision.h"
#include "Framework/Actor.h"

namespace Jackster
{
	CLASS_DEFINITION(CircleCollision);

	void CircleCollision::Update(float dt)
	{
	
	}

	bool CircleCollision::collisionCheck(Collision* collision)
	{
		float distance = m_owner->m_transform.position.distance(collision->GetOwner()->m_transform.position);
		float radius = m_radius + collision->m_radius;
		
		return (distance <= radius);
	}
}
