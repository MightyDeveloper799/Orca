#include "OS.h"
#include <cstdlib>
#include <cstring>

#if defined (_WIN32)
#undef UNICODE
#undef _UNICODE
#include <Windows.h>
#elif defined (__APPLE__)
#include <TargetConditions.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#elif defined(__linux__)
#include <unistd.h>
#include <sys/utsname.h>
#endif

namespace Orca
{
	Platform OS::GetPlatform()
	{
#if defined (_WIN32)
		return Platform::Windows;
#elif defined (__APPLE__)
		return Platform::macOS;
#elif defined (__linux__) || defined(__unix__)
		return Platform::Linux;
#else
		return Platform::Unknown;
#endif
	}

	ProcessorArchitecture OS::GetCPUArchitecture()
	{
#if defined (_M_X64) || defined (__x86_64__)
		return ProcessorArchitecture::x64;
#elif defined (_M_IX86) || defined (__i386__)
		return ProcessorArchitecture::x86;
#elif defined(__aarch64__) || defined(_M_ARM64)
		return ProcessorArchitecture::ARM64;
#elif defined(__arm__) || defined(_M_ARM)
		return ProcessorArchitecture::ARM;
#else
		return ProcessorArchitecture::Unknown;
#endif
	}

	std::string OS::GetPlatformName()
	{
		switch (GetPlatform())
		{
		case Platform::Windows:   return "Windows";
		case Platform::macOS:     return "macOS";
		case Platform::Linux:     return "Linux";
		case Platform::UNIX:      return "UNIX";
		default:			      return "Unknown";
		}
	}

	std::string OS::GetFontDirectory()
	{
		switch (GetPlatform())
		{
		case Platform::Windows:   return "C:/Windows/Fonts";
		case Platform::macOS:     return "/System/Library/Fonts";
		case Platform::Linux:     return "/usr/share/fonts";;
		default:			      return "";
		}
	}

	std::vector<std::string> OS::GetEnvironmentalVariables()
	{
		std::vector<std::string> envs;

#if defined(_WIN32)
		LPCH envStrings = GetEnvironmentStrings();
		if (envStrings)
		{
			LPCH var = envStrings;
			while (*var)
			{
				envs.emplace_back(var);
				var += strlen(var) + 1;
			}

			FreeEnvironmentStringsA(envStrings);
		}
#else
		extern char** environ;
		for (char** env = environ; *env != nullptr; ++env)
		{
			envs.emplace_back(*env);
		}
#endif

		return envs;
	}
}