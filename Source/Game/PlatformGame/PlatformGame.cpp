#include "PlatformGame.h"

#include "Framework/Framework.h"
#include "Core/core.h"
#include "Audio/AudioSystem.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer//ModelManager.h"

namespace Jackster
{

	bool PlatformGame::Initialize()
	{

		//Create players and enemies
		m_scene = std::make_unique<Jackster::Scene>();
		m_scene->Load("scenes/platformscene.json");
		m_scene->Initialize();
		m_scene->SetGame(this);

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
			
			/*auto actor = INSTANTIATE(Actor, "Crate");
			actor->transform.position = { Jackster::random(Jackster::g_renderer.GetWidth()), 100 };
			actor->Initialize();
			m_scene->Add(std::move(actor));*/
			break;
		}
		case PlatformGame::eState::StartGame:
			m_score = 0;
			m_lives = 3;
			m_state = eState::StartLevel;
			break;
		case PlatformGame::eState::StartLevel:
			m_scene->RemoveAll();

			m_state = eState::Game;
			break;
		case PlatformGame::eState::Game:

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
	}

	void PlatformGame::OnPlayerDead(const Jackster::Event& event)
	{
		m_lives--;
		m_state = eState::PlayerDeadStart;
	}
}