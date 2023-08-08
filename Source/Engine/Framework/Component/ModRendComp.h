#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"


namespace Jackster
{
	class ModRendComp : public RenderComponent
	{
	public:
		void Update(float dt);
		void Draw(Renderer& rend);

	private:

	};
}