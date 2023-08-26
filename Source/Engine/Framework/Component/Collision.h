#pragma once
#include "Component.h"

namespace Jackster
{
	class Collision : public Component
	{
	public:
		virtual bool collisionCheck(Collision* collision) { return true; }

	public:
		float m_radius = 0;

	};
}