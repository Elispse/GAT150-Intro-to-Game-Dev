#pragma once
#include <chrono>

namespace Jackster
{
	class Time
	{
	private:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;

	public:
		Time() :
			m_startTime{ clock::now() },
			m_frameTime{ clock::now() }
		{}

		void tick();
		void reset() { m_startTime = clock::now(); }

		clock_rep getElapsedNanoseconds();
		clock_rep getElapsedMicroseconds();
		clock_rep getElapsedMilliseconds();
		float getElapsedSeconds();

		float getTime() const { return m_time; };
		float getDeltaTime() const { return m_deltaTime * m_timeScale; };
		float getUnscaledDeltaTime() const { return m_deltaTime; }

		float getTimeScale() const { return m_timeScale; }
		void setTimeScale(float timeScale) { m_timeScale = m_timeScale; }

	private:
		float m_time;
		float m_deltaTime;
		float m_timeScale = 1;

		clock::time_point m_startTime;
		clock::time_point m_frameTime;
	};

	extern Time g_time;
}