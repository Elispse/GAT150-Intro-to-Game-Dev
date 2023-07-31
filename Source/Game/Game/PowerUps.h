#pragma once
#include "Framework/Actor.h"

class PowerUps : public Jackster::Actor
{
	public:
		/*1UP(float speed, const Jackster::Transform & transform, std::shared_ptr<Jackster::Model> model) :
			Actor{ transform, model },
			m_speed{ speed } 
		{
			m_lifespan = 2.0f
		}*/

		void Update(float dt) override;
		virtual void onCollision(Actor* actor) override;
	private:
		float m_speed = 0;
};