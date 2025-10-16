#include "ScriptComponent.h"
#include "JNIUtils.h"
#include "../Scene/Scene.h"
#include "Core/Logger.h"

namespace Orca
{
	void ScriptComponent::Update(float dt)
	{
		if (behaviour) behaviour->OnUpdate(dt);
	}

	void ScriptComponent::HandleEvent(const std::string& eventName)
	{
		if (behaviour) behaviour->OnEvent(eventName);
	}

	void ScriptComponent::Execute(RuntimeContext& ctx)
	{
		for (const auto& obj : ctx.GetActiveScene()->GetObjects())
		{
			auto script = obj->GetComponent<ScriptComponent>();
			if (!script || !script->IsValid()) continue;

			script->Invoke("onUpdate", ctx.GetDeltaTime());
		}
	}

	bool ScriptComponent::IsValid() const
	{
		return javaObj != nullptr && scriptCls != nullptr;
	}

	void ScriptComponent::Invoke(const std::string& methodName, float arg) const 
	{
		if (!IsValid()) return;

		JNIEnv* env = GetJNIEnv();
		if (!env) return;

		jmethodID method = env->GetMethodID(scriptCls, methodName.c_str(), "(F)V");
		if (method) 
		{
			env->CallVoidMethod(javaObj, method, arg);
		}

		if (env->ExceptionCheck())
		{
			Logger::Log(LogLevel::Error, "Java exception occurred during method invocation: " + methodName);
			env->ExceptionDescribe();
			env->ExceptionClear();
		}

		else 
		{
			Logger::Log(LogLevel::Warning, "Script method has not been found: " + methodName);
		}
	}
}