#include "Enemy.h"
#include "Player.h"
#include "ShipBlaster.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Audio/AudioSystem.h"


#include <Framework/Emitter.h>
#include "Input/InputSystem.h"



void Enemy::Update(float dt)
{
    Actor::Update(dt);

    Jackster::Vector2 forward = Jackster::vec2(0, -1).Rotate(m_transform.rotation);
    auto* player = m_scene->getActor<Player>();
    if (player)
    {
        Jackster::Vector2 direction = player->m_transform.position - m_transform.position;

        float turnAngle = Jackster::vec2::SignedAngle(forward, direction.normalized());
        //turn towards player
        m_transform.rotation += turnAngle * 5 * dt;

        // Check if player is infront
        if (std::fabs(turnAngle) < Jackster::degreesToRadians(30.0f))
        {
            // i see you
        }
    }

    m_transform.position += forward * m_speed * Jackster::g_time.getDeltaTime();
    m_transform.position.x = Jackster::Wrap(m_transform.position.x, (float)Jackster::g_renderer.GetWidth());
    m_transform.position.y = Jackster::Wrap(m_transform.position.y, (float)Jackster::g_renderer.GetHeight());

    m_fireTimer -= dt;
    if (m_fireTimer <= 0)
    {
        m_fireTimer = m_fireRate;
        // Create Weapon
        Jackster::Transform transform{ m_transform.position, m_transform.rotation};
        std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
        weapon->m_tag = "EnemyFire";
        m_scene->Add(std::move(weapon));
        Jackster::g_audioSystem.PlayOneShot("enemy_Shoot");
    }
}

void Enemy::onCollision(Actor* other)
{
    if (other->m_tag == "PlayerFire")
    {

        std::unique_ptr<ShipBlaster> game = std::make_unique<ShipBlaster>();
        game->Initialize();



        m_game->addPoints(100);
        m_health -= 5;
        if (m_health <= 0) m_destroyed = true;

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
        Jackster::Transform transform{ m_transform.position, 0, 1 };
        auto emitter = std::make_unique<Jackster::Emitter>(transform, data);
        emitter->m_lifespan = 0.1f;
        m_scene->Add(std::move(emitter));


    }
}