#pragma once
#include "Framework/Actor.h"

class Player : public Jackster::Actor
{
public:
	Player(float speed, float turnRate, const Jackster::Transform& transform) :
		Actor{ transform },
		m_speed{speed},
		m_turnRate{turnRate}
	{}

	void Update(float dt) override;
	virtual void onCollision(Actor* actor) override;
	bool pu_doubleShot = false;
	//bool 1_UP = false;
private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 100.0f;
};

