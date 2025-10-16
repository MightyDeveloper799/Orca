#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		unsigned int GetID() const;
	private:
		using Uint = unsigned int;
		Uint m_ID;
		std::string m_Path;

		int m_Width, m_Height, m_Channels;
	};
#pragma warning(pop)
}

#endif