#pragma once
#include "Framework/Actor.h"

class Enemy : public Jackster::Actor
{
public:
	Enemy(float speed, float turnrate, const Jackster::Transform& transform, std::shared_ptr<Jackster::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ m_turnRate }
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;
	}

	void Update(float dt) override;
	virtual void onCollision(Actor* actor) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
	float m_health = 10.0f;
};
