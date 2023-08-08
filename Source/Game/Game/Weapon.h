#pragma once
#include "Framework/Actor.h"

class Weapon : public Jackster::Actor
{
public:
	Weapon(float speed, const Jackster::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}

	void Update(float dt) override;
	virtual void onCollision(Actor* actor) override;
private:
	float m_speed = 0;
};

