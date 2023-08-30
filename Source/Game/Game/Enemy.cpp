#include "Enemy.h"
#include "Player.h"
#include "ShipBlaster.h"
#include "Weapon.h"
#include "Audio/AudioSystem.h"

#include "Core/core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"




namespace Jackster
{
    CLASS_DEFINITION(Enemy)

    bool Enemy::Initialize()
    {
        Actor::Initialize();
        // cache off
        m_physicsComponent = getComponent<Physics>();
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
        return true;
    }

    void Enemy::OnDestroy()
    {
        Actor::OnDestroy();
    }

    void Enemy::Update(float dt)
    {
        Jackster::Vector2 forward = Jackster::vec2(0, -1).Rotate(transform.rotation);
        Actor::Update(dt);

        auto* player = m_scene->getActor<Player>();
        if (player)
        {
            Jackster::Vector2 direction = player->transform.position - transform.position;

            float turnAngle = Jackster::vec2::SignedAngle(forward, direction.normalized());
            //turn towards player
            //transform.rotation += turnAngle * 5 * dt;
            m_physicsComponent->ApplyForce(turnAngle);

            // Check if player is infront
            if (std::fabs(turnAngle) < Jackster::degreesToRadians(30.0f))
            {
                // i see you
            }
        }

        m_physicsComponent->ApplyForce(forward * m_speed);
        //transform.position += forward * m_speed * Jackster::g_time.getDeltaTime();
        transform.position.x = Jackster::Wrap(transform.position.x, (float)Jackster::g_renderer.GetWidth());
        transform.position.y = Jackster::Wrap(transform.position.y, (float)Jackster::g_renderer.GetHeight());

        m_fireTimer -= dt;
        if (m_fireTimer <= 0)
        {
            m_fireTimer = m_fireRate;
            // Create Weapon
             auto weapon = INSTANTIATE(Weapon, "Rocket");
                weapon->transform = { transform.position, transform.rotation, 1 };
                weapon->Initialize();
                weapon->tag = "EnemyFire";
                m_scene->Add(std::move(weapon));
        }
    }

    void Enemy::Read(const json_t& value)
    {
        Actor::Read(value);
        READ_DATA(value, m_speed);
        READ_DATA(value, m_turnRate);
        READ_DATA(value, m_fireRate);

    }

    void Enemy::onCollisionEnter(Actor* other)
    {
        if (other->tag == "PlayerFire")
        {
            Jackster::EventManager::Instance().DispatchEvent("AddPoints", 100);
            m_health -= 5;
            if (m_health <= 0) destroyed = true;



            //m_game->addPoints(100);


            Jackster::EmitterData data;
            data.burst = true;
            data.burstCount = 100;
            data.spawnRate = 0;
            data.angle = 0;
            data.angleRange = Jackster::pi;
            data.lifetimeMin = 0.5f;
            data.lifetimeMax = 1.5f;
            data.speedMin = 50;
            data.speedMax = 250;
            data.damping = 0.5f;

            data.color = Jackster::Color{ 1, 0, 0, 1 };

            Jackster::Transform transform{ this->transform.position, 0, 1 };
            auto emitter = std::make_unique<Jackster::Emitter>(transform, data);
            emitter->lifespan = 0.1f;
            m_scene->Add(std::move(emitter));


        }
    }
}
