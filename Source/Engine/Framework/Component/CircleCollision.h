#pragma once
#include "Collision.h"


namespace Jackster
{
	class CircleCollision : public Collision
	{
	public:
		CLASS_DECLARATION(CircleCollision)

		virtual void Update(float dt) override;
		virtual bool collisionCheck(Collision* collision) override;
	};
}