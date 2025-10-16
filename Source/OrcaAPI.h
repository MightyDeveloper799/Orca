#pragma once

#ifdef ORCA_EXPORTS
#define ORCA_API __declspec(dllexport)
#else
#define ORCA_API __declspec(dllimport)
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif