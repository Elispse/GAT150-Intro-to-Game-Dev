#include "Enemy.h"

#include "Core/core.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"

namespace Jackster
{
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();
		// cache off
		m_physicsComponent = getComponent<Jackster::Physics>();
		m_spriteAnimComponent = getComponent<SpriteAnimRenderComponent>();

		return false;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);
		// movement
		float dir = 0;


		// check if position is off screen, if so wrap the position and set physics component to new position
		if ((transform.position.x < 0 || transform.position.x >(float)Jackster::g_renderer.GetWidth()) ||
			(transform.position.y < 0 || transform.position.y >(float)Jackster::g_renderer.GetHeight()))
		{
			transform.position.x = Jackster::Wrap(transform.position.x, (float)Jackster::g_renderer.GetWidth());
			transform.position.y = Jackster::Wrap(transform.position.y, (float)Jackster::g_renderer.GetHeight());

			m_physicsComponent->SetPosition(transform.position);
		}

		Jackster::vec2 forward = Jackster::vec2{ 1, 0 };
		m_physicsComponent->ApplyForce(forward * m_speed * dir);

	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, m_speed);
		READ_DATA(value, jump);
		READ_DATA(value, maxSpeed);
	}

	void Enemy::onCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
			//EVENT_DISPATCH("OnPlayerDead", 0);
		}
		if (other->tag == "Ground") groundCount++;
	}
	void Enemy::onCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}
}