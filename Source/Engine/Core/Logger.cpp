#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace Jackster
{
	Logger g_logger(Jackster::Info, &std::cout, "Log.txt");

	bool Logger::Log(logLevel logLevel, const std::string& filename, int line)
	{
		if (logLevel < m_logLevel)
		{
			return false;
		}
		else 
		{
			return true;
		}

		switch (logLevel)
		{
		case Jackster::Info:
			*this << "INFO: ";
			break;
		case Jackster::Warning:
			*this << "WARNING: ";
			break;
		case Jackster::Error:
			*this << "ERROR: ";
			break;
		case Jackster::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << filename << "(" << line << ")";

		return false;
	}
}