#include "Sprite.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace Jackster
{
	CLASS_DEFINITION(Sprite);


	void Sprite::Update(float dt)
	{

	}

	void Sprite::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void Sprite::Read(const json_t& value)
	{
		READ_DATA(value, textureName);
	}

	bool Sprite::Initialize()
	{
		m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		return true;
	}
}


//