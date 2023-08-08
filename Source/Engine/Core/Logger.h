#pragma once
#include <string>
#include <cassert>
#include <fstream>

#ifdef _DEBUG

#define INFO_LOG(message)	 { if (Jackster::g_logger.Log(Jackster::logLevel::Info, __FILE__, __LINE__)) {Jackster::g_logger << message << "\n"; } }
#define WARNING_LOG(message) { if (Jackster::g_logger.Log(Jackster::logLevel::Warning, __FILE__, __LINE__)) {Jackster::g_logger << message << "\n"; } }
#define ERROR_LOG(message)   { if (Jackster::g_logger.Log(Jackster::logLevel::Error, __FILE__, __LINE__)) {Jackster::g_logger << message << "\n"; } }
#define ASSERT_LOG(condition, message)  { if (!condition && Jackster::g_logger.Log(Jackster::logLevel::Assert, __FILE__, __LINE__)) {Jackster::g_logger << message << "\n"; assert(condition);} }
#else
#define INFO_LOG(message) {}
#define WARNING_LOG(message) {}
#define ERROR_LOG(message) {}
#define ASSERT_LOG(condition, message) {}

#endif // 

namespace Jackster 
{
	enum logLevel
	{
		Info,
		Warning,
		Error,
		Assert
	};



	class Logger
	{
	public:
		Logger(logLevel logLevel, std::ostream* ostream, const std::string& filename = "") :
			m_logLevel{ logLevel },
			m_oStream{ ostream }
		{
			if (!filename.empty()) m_fStream.open(filename);
		}

		bool Log(logLevel logLevel, const std::string& filename, int line);

		template<typename T>
		Logger& operator << (T value);

	private:
		logLevel m_logLevel;
		std::ostream* m_oStream = nullptr;
		std::ofstream m_fStream;
	};

	template<typename T>
	inline Logger& Logger::operator << (T value)
	{
		if (m_oStream) *m_oStream << value;
		if (m_fStream.is_open())
		{
			m_fStream << value;
			m_fStream.flush();
		}
		return *this;
	}

	extern Logger g_logger;
}

