#pragma once
#include <Core/Math/Vector2.h>
#include <Core/Math/Color.h>

namespace Jackster
{
	struct ParticleData
	{
		vec2 position;
		vec2 prevPosition;
		vec2 velocity;
		float damping = 0;
		Color color;
		float lifetimer = 0;
		float lifetime = 0;
	};

	class Particle
	{
	public:
		Particle() = default;
		void Initialize(const ParticleData& data)
		{
			m_data = data;
			m_isActive = true;
		}
		void Update(float dt);
		void Draw(class Renderer& renderer);

		friend class ParticleSystem;

	private:
		ParticleData m_data;
		bool m_isActive = false;
	};
}