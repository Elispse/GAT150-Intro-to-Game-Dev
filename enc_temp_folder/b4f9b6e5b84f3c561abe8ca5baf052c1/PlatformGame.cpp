#include "PlatformGame.h"

#include "Framework/Framework.h"
#include "Core/core.h"
#include "Audio/AudioSystem.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer//ModelManager.h"

#include <iostream>
#include <string>

namespace Jackster
{

	bool PlatformGame::Initialize()
	{

		//Create players and enemies
		m_scene = std::make_unique<Jackster::Scene>();
		m_scene->Load("scenes/platformscene.json");
		m_scene->Load("scenes/tilemap.json");
		m_scene->Initialize();
		m_scene->SetGame(this);

		// coin audio
		Jackster::g_audioSystem.AddAudio("pick_up", "audio/Coin_pickup");

		// add events
		EVENT_SUBSCRIBE("OnAddPoints", PlatformGame::OnAddPoints);
		EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);
		

		return true;
	}

	void PlatformGame::Shutdown()
	{
		//
	}

	void PlatformGame::Update(float dt)
	{
		switch (m_state)
		{
		case PlatformGame::eState::Title:
		{
			m_scene->getActorByName("Title")->active = true;
			m_scene->getActorByName("Player")->active = false;
			m_scene->getActorByName("Enemy")->active = false;
			m_scene->getActorByName("Score")->active = false;
			
			
			if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) m_state = eState::StartGame;
			break;
		}
		case PlatformGame::eState::StartGame:
			m_score = 0;
			m_lives = 3;
			m_state = eState::Game;
			break;
		case PlatformGame::eState::Game:
		{
			m_scene->getActorByName("Title")->active = false;

			m_scene->getActorByName("Player")->active = true;
			m_scene->getActorByName("Crate")->active = true;

			auto scoreRend = m_scene->getActorByName("Score")->getComponent<Jackster::TextRenderComponent>();
			scoreRend->text = "Score: " + std::to_string(m_score);
			m_scene->getActorByName("Score")->active = true;

			m_spawnTimer += dt;
			if (coinCount < 5)
			{
				auto actor = INSTANTIATE(Actor, "Coin");
 				if (m_spawnTimer >= m_spawnTime) {
					m_spawnTimer = 0.0f;
					actor->transform.position = { Jackster::random(Jackster::g_renderer.GetWidth()), 100 };
					actor->Initialize();
					coinCount++;
					m_scene->Add(std::move(actor));
				}
			}

			m_spawnTimer += dt;
			if (m_stateTimer >= 60)
			{
				m_state = eState::GameOver;
			}
		}
			break;
		case PlatformGame::eState::PlayerDeadStart:

			break;
		case PlatformGame::eState::PlayerDead:

			break;
		case PlatformGame::eState::GameOver:

			break;
		default:
			break;
		}
		m_scene->Update(dt);
	}

	void PlatformGame::Draw(Jackster::Renderer& renderer)
	{
		m_scene->Draw(renderer);
	}

	void PlatformGame::OnAddPoints(const Jackster::Event& event)
	{
		m_score += std::get<int>(event.data);
		coinCount--;
		g_audioSystem.PlayOneShot("pick_up");
	}

	void PlatformGame::OnPlayerDead(const Jackster::Event& event)
	{
		m_lives--;
		m_state = eState::PlayerDeadStart;
	}
}