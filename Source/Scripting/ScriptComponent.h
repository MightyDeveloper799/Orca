#pragma once

#ifndef SCRIPT_COMPONENT_H
#define SCRIPT_COMPONENT_H

#include <memory>
#include "ScriptBehaviour.h"
#include "Scene/Component.h"
#include "Asset/Object/Object.h"
#include "Runtime/RuntimeContext.h"
#include <jni.h>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ScriptComponent : public Component
	{
	public:
		void Update(float dt);
		void HandleEvent(const std::string& eventName);
		void Execute(RuntimeContext& ctx);

		bool IsValid() const;
		void Invoke(const std::string& methodName, float arg) const;

	private:
		std::unique_ptr<ScriptBehaviour> behaviour;
		std::string scriptPath;
		jobject javaObj = nullptr;
		jclass scriptCls = nullptr;
		std::string lang;
	};
#pragma warning(pop)
}

#endif