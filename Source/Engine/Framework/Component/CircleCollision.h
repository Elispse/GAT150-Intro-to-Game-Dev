#pragma once
#include "Collision.h"


namespace Jackster
{
	class CircleCollision : public Collision
	{
	public:
		CLASS_DECLARATION(CircleCollision);
		// Inherited via Collision
		virtual void Update(float dt) override;
		virtual bool collisionCheck(Collision* collision) override;
	};
}