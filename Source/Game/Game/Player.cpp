#include "Player.h"
#include "ShipBlaster.h"
#include "Weapon.h"

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
        auto collision = getComponent<Jackster::Collision>();
        if (collision)
        {
            auto renderComponent = getComponent<Jackster::RenderComponent>();
            if (renderComponent)
            {
                float scale = transform.scale;
                collision->m_radius = getComponent<Jackster::RenderComponent>()->GetRadius() * scale;
            }
        }
        return false;
    }

    void Player::Update(float dt)
    {
        Actor::Update(dt);

        // movement
        float rotate = 0;
        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
        //transform.rotation += rotate * m_turnRate * Jackster::g_time.getDeltaTime();
        m_physicsComponent->ApplyTorque(rotate * m_turnRate);

        float thrust = 0;
        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
        Jackster::Vector2 forward = Jackster::vec2(0, -1).Rotate(transform.rotation);

        m_physicsComponent->ApplyForce(forward * m_speed * thrust);

        //m_transform.position += forward * m_speed * thrust * Jackster::g_time.getDeltaTime();
        transform.position.x = Jackster::Wrap(transform.position.x, (float)Jackster::g_renderer.GetWidth());
        transform.position.y = Jackster::Wrap(transform.position.y, (float)Jackster::g_renderer.GetHeight());

        //fire weapon
        switch (pu_doubleShot)
        {
        case false:
            if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
                !Jackster::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
            {
                auto weapon = INSTANTIATE(Weapon, "Rocket");
                weapon->transform = { transform.position, transform.rotation, 1 };
                weapon->Initialize();
                m_scene->Add(std::move(weapon));
            }
            break;
        case true:
            if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
                !Jackster::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
            {
                auto weapon = INSTANTIATE(Weapon, "Rocket");
                weapon->transform = { transform.position + forward * 30, transform.rotation + Jackster::degreesToRadians(10.0f), 1 };
                weapon->Initialize();
                m_scene->Add(std::move(weapon));
            }
            break;
        }
    }

    void Player::Read(const json_t& value)
    {
        Actor::Read(value);
        READ_DATA(value, m_speed);
        READ_DATA(value, m_turnRate);
    }

    void Player::onCollisionEnter(Actor* other)
    {
        if (other->tag == "EnemyFire")
        {
            destroyed = true;
            Jackster::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
            Jackster::EmitterData data;
            data.burst = true;
            data.burstCount = 200;
            data.spawnRate = 100;
            data.angle = 0;
            data.angleRange = Jackster::pi;
            data.lifetimeMin = 0.5f;
            data.lifetimeMax = 2.5f;
            data.speedMin = 50;
            data.speedMax = 250;
            data.damping = 0.5f;
            data.color = Jackster::Color{ 1, 1, 1, 1 };
            Jackster::Transform transform{ transform.position, 0, 1 };
            auto emitter = std::make_unique<Jackster::Emitter>(transform, data);
            emitter->lifespan = 0.1f;
            m_scene->Add(std::move(emitter));
            
        }
    }
}