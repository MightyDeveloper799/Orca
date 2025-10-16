#include "ShaderRegistry.h"
#include "../Core/Logger.h"
#include <filesystem>

namespace Orca
{
	std::unordered_map<std::string, std::unique_ptr<Shader>> ShaderRegistry::s_ShaderCache;
	std::unordered_map<std::string, Shader*> ShaderRegistry::s_NameMap;

	std::string ShaderRegistry::MakeKey(const std::string& vert, const std::string& frag)
	{
		return vert + " | " + frag;
	}

	void ShaderRegistry::Preload(const std::string& name, const std::string& vertPath, const std::string& fragPath)
	{
		try 
		{
			if (!std::filesystem::exists(vertPath) || !std::filesystem::exists(fragPath))
			{
				Logger::Log(LogLevel::Fatal, "Shader file(s) missing for: " + name);
				return;
			}
			auto shader = std::make_unique<Shader>(vertPath, fragPath);
			s_NameMap[name] = shader.get();
			s_ShaderCache[MakeKey(vertPath, fragPath)] = std::move(shader);
		}
		catch (const std::exception& e) 
		{
			Logger::Log(LogLevel::Fatal, "ShaderRegistry::Preload failed for " + name + ": " + e.what());
		}
	}

	Shader* ShaderRegistry::Load(const std::string& vertPath, const std::string& fragPath)
	{
		std::string key = MakeKey(vertPath, fragPath);
		if (s_ShaderCache.find(key) == s_ShaderCache.end())
		{
			s_ShaderCache[key] = std::make_unique<Shader>(vertPath, fragPath);
		}

		return s_ShaderCache[key].get();
	}

	Shader* ShaderRegistry::Get(const std::string& name)
	{
		auto it = s_NameMap.find(name);

		if (it == s_NameMap.end())
		{
			Logger::Log(LogLevel::Warning, "Shader not found in registry: " + name);
			return nullptr;
		}

		return it != s_NameMap.end() ? it->second : nullptr;
	}

	void ShaderRegistry::Clear()
	{
		s_ShaderCache.clear();
		s_NameMap.clear();
	}
}