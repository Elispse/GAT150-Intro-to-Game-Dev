#include "Player.h"

#include "Core/core.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"

namespace Jackster
{
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{
		Actor::Initialize();
		// cache off
		m_physicsComponent = getComponent<Jackster::Physics>();
		m_spriteAnimComponent = getComponent<SpriteAnimRenderComponent>();

		return false;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);
		bool onGround = (groundCount > 0);
		vec2 velocity = m_physicsComponent->m_velocity;

		// movement
		float dir = 0;
		if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		if (dir)
		{
			velocity.x += m_speed * dir * ((onGround) ? 1 : 0.25f) * dt;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);
		}

		if ((transform.position.x < 0 || transform.position.x >(float)Jackster::g_renderer.GetWidth()) ||
			(transform.position.y < 0 || transform.position.y >(float)Jackster::g_renderer.GetHeight()))
		{
			transform.position.x = Jackster::Wrap(transform.position.x, (float)Jackster::g_renderer.GetWidth());
			transform.position.y = Jackster::Wrap(transform.position.y, (float)Jackster::g_renderer.GetHeight());

			m_physicsComponent->SetPosition(transform.position);
		}

		// Jump
		if (onGround && Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!Jackster::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			Jackster::vec2 up = Jackster::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(velocity + (up * jump));
		}

		m_physicsComponent->SetGravityScale((velocity.y > 0) ? 3.0f : 2.0f);

		if (std::fabs(velocity.x) > 0.2f)
		{
			if (dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
			m_spriteAnimComponent->SetSequence("run");
		}
		else
		{
			m_spriteAnimComponent->SetSequence("idle");
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, m_speed);
		READ_DATA(value, jump);
		READ_DATA(value, maxSpeed);
	}

	void Player::onCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			//destroyed = true;
			//EVENT_DISPATCH("OnPlayerDead", 0);
		}
		if (other->tag == "Ground") groundCount++;

		if (other->tag == "Coin")
		{
			EVENT_DISPATCH("OnAddPoints", 100);
			other->destroyed = true;
		}
	}
	void Player::onCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}
}