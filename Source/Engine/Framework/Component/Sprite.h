#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace Jackster
{
	class Sprite : public RenderComponent
	{
	public:
		CLASS_DECLARATION(Sprite);

		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() { return m_texture->GetSize().length() * 0.5f; }


	public:
		res_t<Texture> m_texture;
	};
}