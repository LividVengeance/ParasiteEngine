#pragma once

#include "string"

namespace Parasite
{
	class CShader
	{
	public:
		CShader(const std::string& InVertexSource, const std::string& InFragmentSource);
		~CShader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t RendererID;
	};
}