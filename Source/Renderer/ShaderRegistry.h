#pragma once

#ifndef SHADER_REGISTRY_H
#define SHADER_REGISTRY_H

#include <unordered_map>
#include <memory>
#include "Shader.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ShaderRegistry
	{
	public:
		static void Preload(const std::string& name, const std::string& vertPath, const std::string& fragPath);
		static Shader* Load(const std::string& v_path, const std::string& f_path);
		static Shader* Get(const std::string& name);
		static void Clear();

	private:
		static std::unordered_map<std::string, std::unique_ptr<Shader>> s_ShaderCache;
		static std::unordered_map<std::string, Shader*> s_NameMap;
		static std::string MakeKey(const std::string& vert, const std::string& frag);
	};
#pragma warning(pop)
}

#endif