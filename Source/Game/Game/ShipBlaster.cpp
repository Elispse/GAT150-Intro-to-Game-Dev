#include "ShipBlaster.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"
#include "Core/core.h"
#include "Audio/AudioSystem.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer//ModelManager.h"

namespace Jackster
{

	bool ShipBlaster::Initialize()
	{
		// create font / text objects
		
		m_font = GET_RESOURCE(Jackster::Font, "8bitOperatorPlus8-Bold.ttf", 24);
		
		m_scoreText = std::make_unique<Jackster::Text>(GET_RESOURCE(Jackster::Font, "8bitOperatorPlus8-Bold.ttf", 24));
		m_scoreText->Create(Jackster::g_renderer, "SCORE 0000", Jackster::Color{1, 1, 1, 1});

		m_titleText = std::make_unique<Jackster::Text>(GET_RESOURCE(Jackster::Font, "8bitOperatorPlus8-Bold.ttf", 24));
		m_titleText->Create(Jackster::g_renderer, "SHIPBLASTER", Jackster::Color{1, 1, 1, 1});

		m_gameOverText = std::make_unique<Jackster::Text>(GET_RESOURCE(Jackster::Font, "8bitOperatorPlus8-Bold.ttf", 24));
		m_gameOverText->Create(Jackster::g_renderer, "GAME OVER", Jackster::Color{1, 1, 1, 1});
		
		//load audio
		Jackster::g_audioSystem.AddAudio("hit", "audio/Hit_Hurt.wav");
		Jackster::g_audioSystem.AddAudio("death", "audio/Explosion.wav");
		Jackster::g_audioSystem.AddAudio("player_Shoot", "audio/Laser_Shoot.wav");
		Jackster::g_audioSystem.AddAudio("enemy_Shoot", "audio/Enemy_Shoot.wav");
		Jackster::g_audioSystem.AddAudio("Game_Music", "audio/Main_Music.wav");

		//plays game music
		Jackster::g_audioSystem.PlayOneShot("Game_Music", true);

		//Create players and enemies
		m_scene = std::make_unique<Jackster::Scene>();
		m_scene->Load("Scenes/SpaceScene.json");
		m_scene->Initialize();
		m_scene->SetGame(this);

		// add events
		EVENT_SUBSCRIBE("OnAddPoints", ShipBlaster::OnAddPoints);
		EVENT_SUBSCRIBE("OnPlayerDead", ShipBlaster::OnPlayerDead);

		return true;
	}

	void ShipBlaster::Shutdown()
	{
		//
	}

	void ShipBlaster::Update(float dt)
	{
		switch (m_state)
		{
		case ShipBlaster::eState::Title:
			m_scene->getActorByName("Title")->active = true;
			if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			{
				m_state = eState::StartGame;
				m_scene->getActorByName("Title")->active = false;
			}
			break;
		case ShipBlaster::eState::StartGame:
			m_score = 0;
			m_lives = 3;
			m_state = eState::StartLevel;
			break;
		case ShipBlaster::eState::StartLevel:
			m_scene->RemoveAll();
		{
			//create player
			auto player = INSTANTIATE(Player, "Player");
			player->transform = Jackster::Transform{ {400, 300}, 0, 1 };
			player->Initialize();
			m_scene->Add(std::move(player));
		}
		m_state = eState::Game;
			break;
		case ShipBlaster::eState::Game:
			m_spawnTimer += dt;
			if (enemyCount <= 5)
			{
				if (m_spawnTimer >= m_spawnTime) {
					m_spawnTimer = 0.0f;
					auto enemy = INSTANTIATE(Enemy, "Enemy");
					enemy->transform = Jackster::Transform{ {Jackster::random(800), Jackster::random(600)}, Jackster::randomf(Jackster::pi2), 1 };
					enemy->Initialize();
					m_scene->Add(std::move(enemy));
				}
			}
			break;
		case ShipBlaster::eState::PlayerDeadStart:
			m_stateTimer = 3;
			Jackster::g_audioSystem.PlayOneShot("death");
			if (m_lives == 0) {
				m_state = eState::GameOver;
			}
			else
			{
				m_state = eState::PlayerDead;
			}
			break;
		case ShipBlaster::eState::PlayerDead:
			m_stateTimer -= dt;
			if (m_stateTimer <= 0)
			{
			m_state = eState::StartLevel;
			}
			break;
		case ShipBlaster::eState::GameOver:
			if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			{
				m_state = eState::Title;
			}
			break;
		default:
			break;
		}
		m_scene->Update(dt);
	}

	void ShipBlaster::Draw(Jackster::Renderer& renderer)
	{
		m_scene->Draw(renderer);
		
		
		if (m_state == eState::Title)
		{
			m_titleText->Draw(renderer, 320, 250);
		}
		if (m_state == eState::Game)
		{
			m_scoreText->Draw(renderer, 40, 40);
		}
		if (m_state == eState::GameOver)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
	}

	void ShipBlaster::OnAddPoints(const Jackster::Event& event)
	{
		m_score += std::get<int>(event.data);
	}

	void ShipBlaster::OnPlayerDead(const Jackster::Event& event)
	{
		m_lives--;
		m_state = eState::PlayerDeadStart;
	}
}

