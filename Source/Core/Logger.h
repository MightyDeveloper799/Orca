#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <chrono>
#include <iomanip>
#include"../OrcaAPI.h"

namespace Orca
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Fatal
	};

#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API Logger
	{
	public:
		static void Init(const std::string& logFile = "");
		static void Log(LogLevel level, const std::string& msg);
		
		static void SetLogLevel(LogLevel level);
		static LogLevel GetLogLevel();

	private:
		static std::mutex s_Mutex;
		static std::ofstream s_LogStream;	
		static LogLevel s_CurrentLevel;
		static std::string FormatMessage(LogLevel level, const std::string& msg);
		static std::string Timestamp();
	};
#pragma warning(pop)
}

#endif