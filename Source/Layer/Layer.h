#pragma once

#ifndef LAYER_H
#define LAYER_H

#include "../OrcaAPI.h"
#include <string>

namespace Orca { class Event; }

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)
	class ORCA_API Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
		const std::string& GetName() const { return m_name; }

	protected:
		Layer(const std::string& name = "Layer") : m_name(name) {}
	private:
		std::string m_name;
	};
#pragma warning(pop)
}

#endif