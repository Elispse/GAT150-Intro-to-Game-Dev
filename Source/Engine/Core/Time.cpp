#include "Time.h"

namespace Jackster
{
	Time g_time;

	void Time::tick()
	{
		clock_duration duration = clock::now() - m_startTime;
		m_time = duration.count() / static_cast<float>(clock_duration::period::den);

		duration = clock::now() - m_frameTime;
		m_deltaTime = duration.count() / static_cast<float>(clock_duration::period::den);

		m_frameTime = clock::now();
	}

	Time::clock_rep Time::getElapsedNanoseconds()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - m_startTime).count();
	}

	Time::clock_rep Time::getElapsedMicroseconds()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - m_startTime).count();
	}

	Time::clock_rep Time::getElapsedMilliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - m_startTime).count();
	}

	float Time::getElapsedSeconds()
	{
		return (clock::now() - m_startTime).count() / static_cast<float>(clock_duration::period::den);
	}
}

