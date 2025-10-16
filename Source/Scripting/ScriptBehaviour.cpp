#include "ScriptBehaviour.h"
#include "ScriptEngine.h"

namespace Orca
{
	class LuaBehaviour : public ScriptBehaviour
	{
	public:
		LuaBehaviour(const std::string& file) : scriptFile(file) {}
		void OnUpdate(float dt) override
		{
			ScriptEngine().RunLuaScript(scriptFile);
		}

		void OnEvent(const std::string& e) override
		{
			//Nothing (for now)
		}

	private:
		std::string scriptFile;
	};

	class JavaBehaviour : public ScriptBehaviour
	{
	public:
		JavaBehaviour(const std::string& className) {}

		void OnUpdate(float dt) override
		{
			ScriptEngine().RunJavaScript(javaClass, "onUpdate");
		}

		void OnEvent(const std::string& e) override
		{
			ScriptEngine().RunJavaScript(javaClass, "onEvent");
		}

	private:
		std::string javaClass;
	};
}