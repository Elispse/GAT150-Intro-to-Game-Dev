#pragma once
#include "Framework/Actor.h"
#include "Core/Json.h"

namespace Jackster
{
	class Weapon : public Jackster::Actor
	{
	public:

		CLASS_DECLARATION(Weapon)

		bool Initialize() override;
		void Update(float dt) override;
		virtual void onCollision(Actor* actor) override;

	private:
		float speed = 0;
	};
}