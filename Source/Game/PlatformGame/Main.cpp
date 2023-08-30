#include "PlatformGame.h"

#include "Core/core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Physics/.vs/Physics/PhysicsSystem.h"
#include "Renderer/ParticleSystem.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>
#include <functional>

int main(int argc, char* argv[]) {



    INFO_LOG("Initializng Engine...")

    Jackster::MemoryTracker::Initialize();
    Jackster::seedRandom((unsigned)time(nullptr));
    Jackster::setFilePath("assets/platformer");


    Jackster::g_renderer.Initialize();
    Jackster::g_renderer.CreateWindow("GAT150", 800, 600);

    Jackster::g_inputSystem.Initialize();
    Jackster::g_audioSystem.Initialize();
    Jackster::PhysicsSystem::Instance().Initialize();

    // Create Game
    std::unique_ptr<Jackster::PlatformGame> game = std::make_unique<Jackster::PlatformGame>();
    game->Initialize();

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
        Jackster::PhysicsSystem::Instance().Update(Jackster::g_time.getDeltaTime());

        if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
        {
            quit = true;
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

        //ends frame
        Jackster::g_renderer.EndFrame();
    }
    return 0;
}