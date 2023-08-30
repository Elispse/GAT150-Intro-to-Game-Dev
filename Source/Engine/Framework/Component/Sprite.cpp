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
		renderer.DrawTexture(m_texture.get(), source, m_owner->transform);
	}

	void Sprite::Read(const json_t& value)
	{
		READ_DATA(value, textureName);
		READ_DATA(value, source);
		READ_DATA(value, flipH);
		READ_DATA(value, origin);
	}

	bool Sprite::Initialize()
	{
		if(!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		if (source.w == 0 && source.h == 0)
		{
			if (m_texture)
			{
				source.x = 0;
				source.y = 0;
				source.w = m_texture->GetSize().x;
				source.h = m_texture->GetSize().y;
			}
		}

		return true;
	}
}