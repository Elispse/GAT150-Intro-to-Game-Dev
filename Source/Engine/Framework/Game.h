#pragma once
#include <memory>

namespace Jackster
{
	class Renderer;
	class Scene;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& renderer) = 0;

		int getScore() const { return m_score; }
		void addPoints(int points) { m_score += points; }

		int getLives() const { return m_lives; }
		void setLives(int lives) { m_lives = lives; }

		std::unique_ptr<Scene> m_scene;
	protected:

		int m_score = 0;
		int m_lives = 0;
	};
}