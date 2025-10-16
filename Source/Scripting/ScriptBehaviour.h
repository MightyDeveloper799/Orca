#pragma once

#ifndef SCRIPT_BEHAVIOUR_H
#define SCRIPT_BEHAVIOUR_H

#include <string>
#include "../OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API ScriptBehaviour
	{
	public:
		virtual ~ScriptBehaviour() = default;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnEvent(const std::string& eventName) = 0;
	};
#pragma warning(pop)
}

#endif