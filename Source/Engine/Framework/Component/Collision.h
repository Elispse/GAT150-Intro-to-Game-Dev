#pragma once
#include "Components.h"

namespace Jackster
{
	class Collision : public Component
	{
	public:

		virtual bool collisionCheck(Collision* collision) = 0;
	public:
		float m_radius = 0;
	};
}