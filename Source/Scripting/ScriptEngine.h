#pragma once

#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include <string>
#include <sol.hpp>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ScriptEngine
	{
	public:
		void Init();
		void Shutdown();

		void RunJavaScript(const std::string& className, const std::string& methodName);
		void RunLuaScript(const std::string& file);

	private:
		lua_State* l_State = nullptr;
	};
#pragma warning(pop)
}

#endif