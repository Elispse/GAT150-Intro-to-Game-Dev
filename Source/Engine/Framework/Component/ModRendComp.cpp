#include "ModRendComp.h"
#include "Framework/Actor.h"

namespace Jackster
{
	void ModRendComp::Update(float dt)
	{

	}

	void ModRendComp::Draw(Renderer& rend)
	{
		m_model->draw(rend, m_owner->m_transform);
	}
}