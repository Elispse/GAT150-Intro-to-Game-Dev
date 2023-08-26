#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "Core/core.h"

namespace Jackster
{
    CLASS_DEFINITION(Weapon)

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
                float scale = transform.scale;
                collision->m_radius = getComponent<Jackster::RenderComponent>()->GetRadius() * scale;
            }
        }
        return true;
    }

    void Weapon::Update(float dt)
    {
        Actor::Update(dt);
    
        Jackster::Vector2 forward = Jackster::vec2(0, -1).Rotate(transform.rotation);
        transform.position += forward * speed * Jackster::g_time.getDeltaTime();
        if (transform.position.x > Jackster::g_renderer.GetWidth() && transform.position.y > Jackster::g_renderer.GetHeight())
        {
            destroyed = true;
        }
    }

    void Weapon::onCollision(Actor* other)
    {
        if (other->tag != tag)
        {
            destroyed = true;
        }
    }

    void Weapon::Read(const Jackster::json_t& value)
    {
        Actor::Read(value);

        READ_DATA(value, speed);
    }
}
