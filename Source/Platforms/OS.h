#pragma once

#ifndef OS_H
#define OS_H

#include <string>
#include <vector>

namespace Orca
{
	enum class Platform
	{
		Windows,
		macOS,
		Linux,
		UNIX,
		Unknown = 0x00
	};

	enum class ProcessorArchitecture
	{
		x86,
		x64,
		ARM,
		ARM64,
		Unknown = 0x00
	};

#pragma warning(push)
#pragma warning(disable : 4251)

	class OS
	{
	public:
		static Platform GetPlatform();
		static ProcessorArchitecture GetCPUArchitecture();
		static std::string GetPlatformName();
		static std::string GetFontDirectory();
		static std::vector<std::string> GetEnvironmentalVariables();
	};
#pragma warning(pop)
}

#endif