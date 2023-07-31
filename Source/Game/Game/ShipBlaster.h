#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class ShipBlaster : public Jackster::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOver
	};

public:


	// Inherited via Game
	virtual bool Initialize() override;

	virtual void Shutdown() override;

	virtual void Update(float dt) override;

	virtual void Draw(Jackster::Renderer& renderer) override;

	void setState(eState state) { m_state = state; }

	void endGameFireworks();
	
private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0.0f;
	float m_spawnTime = 3.0f;
	unsigned short enemyCount = 0;
	float m_stateTimer = 0;

	std::shared_ptr<Jackster::Font> m_font;
	std::unique_ptr<Jackster::Text> m_scoreText;
	std::unique_ptr<Jackster::Text> m_titleText;
	std::unique_ptr<Jackster::Text> m_gameOverText;

};