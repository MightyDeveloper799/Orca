#include "Logger.h"

namespace Orca
{
	std::mutex Logger::s_Mutex;
	std::ofstream Logger::s_LogStream;
	LogLevel Logger::s_CurrentLevel = LogLevel::Info;

	void Logger::Init(const std::string& logFile)
	{
		std::lock_guard<std::mutex> lock(s_Mutex);
		if (!logFile.empty())
		{
			s_LogStream.open(logFile, std::ios::out | std::ios::app);
		}
	}

	void Logger::Log(LogLevel level, const std::string& msg)
	{
		std::lock_guard<std::mutex> lock(s_Mutex);
		if (level < s_CurrentLevel)
		{
			return;
		}

		std::string formatted = FormatMessage(level, msg);

		std::cout << formatted << std::endl;

		if (s_LogStream.is_open())
		{
			s_LogStream << formatted << std::endl;
		}

		if (level == LogLevel::Fatal)
		{
			std::terminate();
		}
	}

	void Logger::SetLogLevel(LogLevel level)
	{
		std::lock_guard<std::mutex> lock(s_Mutex);
		s_CurrentLevel = level;
	}

	LogLevel Logger::GetLogLevel()
	{
		std::lock_guard<std::mutex> lock(s_Mutex);
		return s_CurrentLevel;
	}

	std::string Logger::FormatMessage(LogLevel level, const std::string& msg)
	{
		std::ostringstream oss;
		oss << Timestamp() << " ";
		
		switch (level)
		{
		case LogLevel::Info:    oss << "[INFO] "; break;
		case LogLevel::Warning: oss << "[WARNING] "; break;
		case LogLevel::Error:   oss << "[ERROR] "; break;
		case LogLevel::Fatal:   oss << "[FATAL] "; break;
		}

		oss << msg;
		return oss.str();
	}

	std::string Logger::Timestamp()
	{
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);
		std::tm tm;
#if defined(_WIN32)
		localtime_s(&tm, &time);
#else
		localtime_r(&time, &tm);
#endif

		std::ostringstream oss;
		oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}
}