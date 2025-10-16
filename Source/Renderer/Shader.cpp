#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../Core/Logger.h"

namespace Orca
{
	Shader::Shader(const std::string& vertPath, const std::string& fragPath)
		: m_ID(0)
	{
		try
		{
			std::string vertexSrc = LoadFile(vertPath);
			std::string fragSrc = LoadFile(fragPath);
			LinkProgram(vertexSrc, fragSrc);
		}

		catch (const std::exception& e)
		{
			Logger::Log(LogLevel::Fatal, std::string("Failed to initialize shader from paths [") + vertPath + " & " + fragPath + "]: " + e.what());
		}
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ID);
	}

	void Shader::Bind() const
	{
		if (m_ID == 0)
		{
			Logger::Log(LogLevel::Error, "Shader::Bind called with invalid program ID (0). Shader is not valid.");
			return;
		}

		glUseProgram(m_ID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetFloat(const std::string& name, float val) const
	{
		std::cerr << "Attempting to set uniform (Float) :" << name << "/n";

		GLint loc = GetUniformLocation(name);
		if (loc == -1)
		{
			return;
		}
		glUniform1f(loc, val);
	}

	void Shader::SetInt(const std::string& name, int val) const
	{
		std::cerr << "Attempting to set uniform (Int) :" << name << "/n";

		GLint loc = GetUniformLocation(name);
		if (loc == -1)
		{
			return;
		}
		glUniform1i(loc, val);
	}

	void Shader::SetVec3(const std::string& name, const glm::vec3& val) const
	{
		std::cerr << "Attempting to set uniform (Vec3) :" << name << "/n";

		GLint loc = GetUniformLocation(name);
		if (loc == -1) 
		{
			return;
		}
		glUniform3f(loc, val.x, val.y, val.z);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& val) const
	{
		std::cerr << "Attempting to set uniform (Mat4) :" << name << "/n";
		
		GLint loc = GetUniformLocation(name);
		if (loc == -1)
		{
			return;
		}

		glUniformMatrix4fv(loc, 1, GL_FALSE, &val[0][0]);
	}

	std::string Shader::LoadFile(const std::string& path)
	{
		std::ifstream file(path);

		if (!file.is_open())
		{
			Logger::Log(LogLevel::Warning, "Can't open shader file: " + path);
			return "";
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string content = buffer.str();

		if (content.empty())
		{
			Logger::Log(LogLevel::Warning, "Shader file is empty: " + path);
		}

		return content;
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		if (source.empty())
		{
			Logger::Log(LogLevel::Error, "Shader source is empty. Compilation aborted.");
			return 0;
		}

		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success) 
		{
			char info[512];
			glGetShaderInfoLog(id, 512, nullptr, info);
			Logger::Log(LogLevel::Error,
				std::string("Shader compilation failed for ") + (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") + " shader:\n" + info);
		}

		return id;
	}

	void Shader::LinkProgram(const std::string& vertexSrc, const std::string& fragmentSrc) 
	{
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

		if (vs == 0 || fs == 0) 
		{
			if (vs != 0) glDeleteShader(vs);
			if (fs != 0) glDeleteShader(fs);
			throw std::runtime_error("Shader compilation failed—vertex or fragment source is invalid.");
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vs);
		glAttachShader(m_ID, fs);
		glLinkProgram(m_ID);

		int success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success) 
		{
			char info[512];
			glGetProgramInfoLog(m_ID, 512, nullptr, info);
			Logger::Log(LogLevel::Fatal, std::string("Shader linking failed for program ID ") + std::to_string(m_ID) + ":\n" + info);
			glDeleteProgram(m_ID);
			m_ID = 0;
			throw std::runtime_error(std::string("Shader linking failed:\n") + info);
		}

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	int Shader::GetUniformLocation(const std::string& name) const
	{
		if (m_ID == 0)
		{
			std::cerr << "GetUniformLocation called on invalid shader program\n";
			return -1;
		}

		auto& uniformCache = const_cast<std::unordered_map<std::string, int>&>(m_UniformCache);

		if (uniformCache.find(name) != uniformCache.end())
			return uniformCache[name];

		int location = glGetUniformLocation(m_ID, name.c_str());
		uniformCache[name] = location;

		if (location == -1)
		{
			Logger::Log(LogLevel::Warning, "Uniform '" + name + "' not found (or optimized out) in Shader ID " + std::to_string(m_ID));
		}

		return location;
	}
}