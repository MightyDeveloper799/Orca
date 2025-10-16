#pragma once

#ifndef MEMORY_H
#define MEMORY_H

#include <memory>

namespace Orca
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateReference(Args& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}

#endif