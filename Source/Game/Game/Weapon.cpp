#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "Core/core.h"

bool Weapon::Initialize()
{
    Actor::Initialize();
    // cache off
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
    return true;
}

void Weapon::Update(float dt)
{
    Actor::Update(dt);
    
    Jackster::Vector2 forward = Jackster::vec2(0, -1).Rotate(m_transform.rotation);
    m_transform.position += forward * m_speed * Jackster::g_time.getDeltaTime();
    if (m_transform.position.x > Jackster::g_renderer.GetWidth() && m_transform.position.y > Jackster::g_renderer.GetHeight())
    {
        m_destroyed = true;
    }
}

void Weapon::onCollision(Actor* other)
{
    if (other->m_tag != m_tag)
    {
        m_destroyed = true;
    }
}