#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace Jackster
{
	bool Logger::Log(logLevel logLevel, const std::string& filename, int line)
	{
		if (logLevel < m_logLevel) return false;

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