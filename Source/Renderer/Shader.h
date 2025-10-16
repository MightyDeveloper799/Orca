#pragma once

#ifndef SHADER_H
#define SHADER_H

#pragma message("Compiling Shader.h from: " __FILE__)

#include <string>
#include <unordered_map>
#include <cstdint>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class Shader
	{
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetFloat(const std::string& name, float val) const;
		void SetInt(const std::string& name, int val) const;
		void SetVec3(const std::string& name, const glm::vec3& val) const;
		void SetMat4(const std::string& name, const glm::mat4& val) const;
		bool IsValid() const { return m_ID != 0; }

		unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID;
		mutable std::unordered_map<std::string, int> m_UniformCache;

		std::string LoadFile(const std::string& path);
		unsigned int CompileShader(unsigned int type, const std::string& src);
		void LinkProgram(const std::string& vertSrc, const std::string& fragSrc);
		int GetUniformLocation(const std::string& name) const;
	};
#pragma warning(pop)
}

#endif