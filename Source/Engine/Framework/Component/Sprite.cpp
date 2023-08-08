#include "Sprite.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Actor.h"

namespace Jackster
{
	void Sprite::Update(float dt)
	{

	}

	void Sprite::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform.position.x, m_owner->m_transform.position.y, radiansToDegrees(m_owner->m_transform.rotation));
	}

}