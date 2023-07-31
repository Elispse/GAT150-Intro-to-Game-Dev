#include "ShipBlaster.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"
#include "Input/InputSystem.h"

#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include <Framework/Emitter.h>

bool ShipBlaster::Initialize()
{
	// create font / text objects
	m_font = std::make_shared<Jackster::Font>("8bitOperatorPlus8-Bold.ttf", 24);

	m_scoreText = std::make_unique<Jackster::Text>(m_font);
	m_scoreText->Create(Jackster::g_renderer, "SCORE 0000", Jackster::Color{1, 1, 1, 1});

	m_titleText = std::make_unique<Jackster::Text>(m_font);
	m_titleText->Create(Jackster::g_renderer, "SHIPBLASTER", Jackster::Color{1, 1, 1, 1});

	m_gameOverText = std::make_unique<Jackster::Text>(m_font);
	m_gameOverText->Create(Jackster::g_renderer, "GAME OVER", Jackster::Color{1, 1, 1, 1});

	//load audio
	Jackster::g_audioSystem.AddAudio("hit", "Hit_Hurt.wav");
	Jackster::g_audioSystem.AddAudio("death", "Explosion.wav");
	Jackster::g_audioSystem.AddAudio("player_Shoot", "Laser_Shoot.wav");
	Jackster::g_audioSystem.AddAudio("enemy_Shoot", "Enemy_Shoot.wav");
	Jackster::g_audioSystem.AddAudio("Game_Music", "Main_Music.wav");

	//plays game music
	Jackster::g_audioSystem.PlayOneShot("Game_Music", true);

	//Create players and enemies
	m_scene = std::make_unique<Jackster::Scene>();

	return false;
}

void ShipBlaster::Shutdown()
{

}

void ShipBlaster::Update(float dt)
{
	switch (m_state)
	{
		
	case ShipBlaster::eState::Title:
		if (Jackster::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
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
		std::unique_ptr<Player> player = std::make_unique<Player>(10.0f, Jackster::pi, Jackster::Transform{ {400, 300}, 0, 6 }, Jackster::g_MM.get("Ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		player->SetDamping(0.9f);
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

				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(150.0f, Jackster::pi, Jackster::Transform{ {Jackster::random(0, 800), Jackster::random(0, 600) }, Jackster::randomf(Jackster::pi2), 6 }, Jackster::g_MM.get("EnemyShip.txt"));
				enemy->m_tag = "Enemy";
				enemy->m_game = this;
				m_scene->Add(std::move(enemy));
			}
		}
		m_scoreText->Create(Jackster::g_renderer, "Score: " + std::to_string(m_score), { 1, 1, 1, 1 });
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
		endGameFireworks();
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

	m_scene->Draw(renderer);
}

void ShipBlaster::endGameFireworks()
{
	for (size_t i = 0; i < 5; i++)
	{
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
		Jackster::Transform transform{ Jackster::random(0, 800), 0, 1 };
		auto emitter = std::make_unique<Jackster::Emitter>(transform, data);
		emitter->m_lifespan = 0.1f;
		m_scene->Add(std::move(emitter));
	}

}