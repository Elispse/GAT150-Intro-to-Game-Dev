#include "Core/core.h"
#include "Renderer/Renderer.h"

#include "Input/InputSystem.h"

#include "Audio/AudioSystem.h"

#include "Framework/Framework.h"

#include "Physics/PhysicsSystem.h"
#include "Physics/.vs/Physics/PhysicsSystem.h"

#include "ShipBlaster.h"
#include "Renderer/ParticleSystem.h"

#include <functional>


class Star {
public:
    Star(const Jackster::vec2& pos, const Jackster::vec2& vel) :
        m_pos{ pos },
        m_vel{ vel }
    {}

    void Update(int width, int height) {
        m_pos += m_vel * Jackster::g_time.getDeltaTime();
        if (m_pos.x >= width) m_pos.x = 0;
        if (m_pos.y >= height) m_pos.y = 0;
    }

    void Draw(Jackster::Renderer& renderer) {
        renderer.drawPoint(m_pos.x, m_pos.y);
    }
public:
    Jackster::vec2 m_pos;
    Jackster::vec2 m_vel;
};

void print(int i)
{
    std::cout << i << std::endl;
}

int main(int argc, char* argv[]) {

    void (*func_ptr)(int) = &print;
    func_ptr(5);

    INFO_LOG("Initializng Engine...")

        Jackster::MemoryTracker::Initialize();
    Jackster::seedRandom((unsigned)time(nullptr));
    Jackster::setFilePath("assets");


    Jackster::g_renderer.Initialize();
    Jackster::g_renderer.CreateWindow("CSC196", 800, 600);

    Jackster::g_inputSystem.Initialize();
    Jackster::g_audioSystem.Initialize();
    Jackster::PhysicsSystem::Instance().Initialize();


    std::unique_ptr<Jackster::ShipBlaster> game = std::make_unique<Jackster::ShipBlaster>();
    game->Initialize();

    std::vector<Star> stars;
    for (int i = 0; i < 1000; i++)
    {
        Jackster::vec2 pos(Jackster::Vector2(Jackster::random(Jackster::g_renderer.GetWidth()), Jackster::random(Jackster::g_renderer.GetHeight())));
        Jackster::vec2 vel(Jackster::randomf(1, 4), 0.0f);

        stars.push_back(Star(pos, vel));
    }

    Jackster::vec2 position{400, 300};
    float speed = 150;
    float scale = 5;

    // Main game loop
    bool quit = false;
    while (!quit)
    {
        Jackster::g_time.tick();
        Jackster::g_inputSystem.Update();
        Jackster::g_audioSystem.Update();
        Jackster::g_particleSystem.Update(Jackster::g_time.getDeltaTime());

        

        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
        {
            quit = true;
        }

        if (Jackster::g_inputSystem.GetMouseButtonDown(0))
        {
            Jackster::EmitterData data;
            data.burst = true;
            data.burstCount = 100;
            data.spawnRate = 200;
            data.angle = 0;
            data.angleRange = Jackster::pi;
            data.lifetimeMin = 0.5f;
            data.lifetimeMin = 1.5f;
            data.speedMin = 50;
            data.speedMax = 250;
            data.damping = 0.5f;
            data.color = Jackster::Color{ 1, 1, 1, 1 };
            Jackster::Transform transform{ { Jackster::g_inputSystem.GetMousePosition() }, 0, 1 };
            auto emitter = std::make_unique<Jackster::Emitter>(transform, data);
            emitter->lifespan = 1.0f;
            game->m_scene->Add(std::move(emitter));
        }

        //update Game
        game->Update(Jackster::g_time.getDeltaTime());

        Jackster::vec2 direction;
        position += direction * speed * Jackster::g_time.getDeltaTime();

        // Draw Game
        Jackster::g_renderer.setColor(0, 0, 0, 0);
        Jackster::g_renderer.BeginFrame();

        //draws frame
        game->Draw(Jackster::g_renderer);
        Jackster::g_particleSystem.Draw(Jackster::g_renderer);

        //Update stars
        for (auto& star : stars)
        {
            star.Update(Jackster::g_renderer.GetWidth(), Jackster::g_renderer.GetHeight());

            //star.m_pos.x + 1;
            star.m_pos.y += 0.3f;

            if (star.m_pos.x >= Jackster::g_renderer.GetWidth()) star.m_pos.x = 0;
            if (star.m_pos.y >= Jackster::g_renderer.GetHeight()) star.m_pos.y = 0;

            Jackster::g_renderer.setColor(Jackster::random(256), 255, 255, 255);
            Jackster::g_renderer.setColor(Jackster::random(256), Jackster::random(256), Jackster::random(256), 255);
            //draw
            Jackster::g_renderer.drawPoint(star.m_pos.x, star.m_pos.y);
        }


        //ends frame
        Jackster::g_renderer.EndFrame();
    }
    stars.clear();

    return 0;
}