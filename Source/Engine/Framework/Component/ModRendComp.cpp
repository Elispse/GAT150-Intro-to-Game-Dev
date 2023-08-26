#include "ModRendComp.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace Jackster
{
	CLASS_DEFINITION(ModRendComp)

	bool ModRendComp::Initialize()
	{
		m_model = GET_RESOURCE(Model, modelName);

		return true;
	}

	void ModRendComp::Update(float dt)
	{

	}

	void ModRendComp::Draw(Renderer& rend)
	{
		m_model->draw(rend, m_owner->transform);
	}

	void ModRendComp::Read(const json_t& value)
	{
		READ_DATA(value, modelName);
	}
}