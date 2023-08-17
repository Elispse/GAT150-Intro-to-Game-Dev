#include "Player.h"
#include "ShipBlaster.h"
#include "Weapon.h"

#include "Core/core.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"

bool Player::Initialize()
{
    Actor::Initialize();
    // cache off
    m_physics = getComponent<Jackster::Physics>();
    auto collision = getComponent<Jackster::Collision>();
    if (collision)
    {
        auto renderComponent = getComponent<Jackster::RenderComponent>();
        if (renderComponent)
        {
            float scale = m_transform.scale;
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
    m_transform.rotation += rotate * m_turnRate * Jackster::g_time.getDeltaTime();

    float thrust = 0;
    if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
    Jackster::Vector2 forward = Jackster::vec2(0, -1).Rotate(m_transform.rotation);

    m_physics->ApplyForce(forward * m_speed * thrust);

    //m_transform.position += forward * m_speed * thrust * Jackster::g_time.getDeltaTime();
    m_transform.position.x = Jackster::Wrap(m_transform.position.x, (float)Jackster::g_renderer.GetWidth());
    m_transform.position.y = Jackster::Wrap(m_transform.position.y, (float)Jackster::g_renderer.GetHeight());

    // fire weapon
    switch (pu_doubleShot)
    {
    case false:
        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
            !Jackster::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
        {
            // Create Weapon
            Jackster::Transform transform{ m_transform.position, m_transform.rotation, 1};
            std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform);
            weapon->m_tag = "PlayerFire";

            std::unique_ptr<Jackster::Sprite> component = std::make_unique<Jackster::Sprite>();
            component->m_texture = GET_RESOURCE(Jackster::Texture, "Missile.png", Jackster::g_renderer);
            weapon->addComponent(std::move(component));

            auto collision = std::make_unique<Jackster::CircleCollision>();
            collision->m_radius = 30.0f;
            weapon->addComponent(std::move(collision));

            weapon->Initialize();
            m_scene->Add(std::move(weapon));
            Jackster::g_audioSystem.PlayOneShot("player_Shoot");
        }
        break;
    case true:
            if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
                !Jackster::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
            {
                // Create Weapon
                Jackster::Transform transform{ m_transform.position, m_transform.rotation + Jackster::degreesToRadians(10.0f), 1};
                std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform);
                weapon->m_tag = "PlayerFire";

                std::unique_ptr<Jackster::Sprite> component = std::make_unique<Jackster::Sprite>();
                component->m_texture = GET_RESOURCE(Jackster::Texture, "Missile.png", Jackster::g_renderer);
                weapon->addComponent(std::move(component));

                auto collision = std::make_unique<Jackster::CircleCollision>();
                collision->m_radius = 10.0f;
                weapon->addComponent(std::move(collision));

                weapon->Initialize();
                m_scene->Add(std::move(weapon));

                Jackster::Transform transform2{ m_transform.position, m_transform.rotation - Jackster::degreesToRadians(10.0f), 1};
                weapon = std::make_unique<Weapon>(400.0f, transform2);
                weapon->m_tag = "PlayerFire";

                std::unique_ptr<Jackster::Sprite> component2 = std::make_unique<Jackster::Sprite>();
                component2->m_texture = GET_RESOURCE(Jackster::Texture, "Missile.png", Jackster::g_renderer);
                weapon->addComponent(std::move(component2));

                collision = std::make_unique<Jackster::CircleCollision>();
                collision->m_radius = 10.0f;
                weapon->addComponent(std::move(collision));

                weapon->Initialize();
                m_scene->Add(std::move(weapon));
                Jackster::g_audioSystem.PlayOneShot("shoot");
            }
            break;
        }
}

void Player::onCollision(Actor* other)
{
    if (other->m_tag == "EnemyFire")
    {
        m_health -= 50;
        if (m_health <= 0) {
            m_destroyed = true;
            m_game->setLives(m_game->getLives() - 1);
            dynamic_cast<ShipBlaster*>(m_game)->setState(ShipBlaster::eState::PlayerDeadStart);


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
            Jackster::Transform transform{ m_transform.position, 0, 1 };
            auto emitter = std::make_unique<Jackster::Emitter>(transform, data);
            emitter->m_lifespan = 0.1f;
            m_scene->Add(std::move(emitter));
        }
    }

    if (other->m_tag == "1UP") {
        m_health++;
    }
}