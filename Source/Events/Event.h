#pragma once

#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <unordered_map>
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	enum class EventType
	{
		None = 0x00,
		KeyPressed,
		KeyRelease,
		MouseMoved,
		MouseClicked,
		Collision,
		ScriptTrigger,
		Custom
	};

	class ORCA_API Event
	{
	public:
		Event(EventType type, const std::string& name) : type(type), name(name) {}
		virtual ~Event() = default;

		EventType GetType() const { return type; }
		const std::string& GetName() const { return name; }

		void SetData(const std::string& key, const std::string& value) 
		{
			data[key] = value;
		}

		const std::string& GetData(const std::string& key) const 
		{
			static std::string empty;
			auto it = data.find(key);
			return it != data.end() ? it->second : empty;
		}

	private:
		EventType type;
		std::string name;
		std::unordered_map<std::string, std::string> data;
	};
#pragma warning(pop)
}

#endif