#include "ScriptEngine.h"
#include "ScriptBindings/JavaAPI.h"
#include <iostream>

namespace Orca
{
	void ScriptEngine::Init()
	{
		l_State = luaL_newstate();
		luaL_openlibs(l_State);
		ScriptBindings::InitJavaVM();
	}

	void ScriptEngine::Shutdown()
	{
		if (l_State) lua_close(l_State);
		ScriptBindings::DestroyJavaVM();
	}

	void ScriptEngine::RunJavaScript(const std::string& className, const std::string& methodName)
	{
		ScriptBindings::CallJavaMethod(className, methodName);
	}

	void ScriptEngine::RunLuaScript(const std::string& file)
	{
		if (luaL_dofile(l_State, file.c_str()) != LUA_OK)
		{
			std::cerr << "Error at: " << lua_tostring(l_State, -1) << std::endl;
		}
	}
}