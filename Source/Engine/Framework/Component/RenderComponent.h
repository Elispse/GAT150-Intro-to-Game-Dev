#pragma once
#include "Components.h"

namespace Jackster
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}
