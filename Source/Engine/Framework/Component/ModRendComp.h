#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"


namespace Jackster
{
	class ModRendComp : public RenderComponent
	{
	public:
		void Update(float dt);
		void Draw(class Renderer& rend) override;

		virtual float GetRadius() override { return m_model->getRadius(); }
	private:
		res_t<Model> m_model;
	};
}