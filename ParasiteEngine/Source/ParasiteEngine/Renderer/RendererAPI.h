#pragma once

#include "glm/glm.hpp"
#include "VertexArray.h"


namespace Parasite
{
	class CRendererAPI
	{
	public:
		enum class EAPI
		{
			None = 0,
			OpenGL,
		};

	public:
		virtual void Init() = 0;

		virtual void SetViewport(uint32_t InX, uint32_t InY, uint32_t InWidth, uint32_t InHeight) = 0;

		virtual void SetClearColour(const glm::vec4& InColour) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const TSharedPtr<CVertexArray>& InVertexArray, uint32_t InIndexCount = 0) = 0;

		inline static EAPI GetRendererAPI() { return RendererAPI; }

	private:
		static EAPI RendererAPI;
	};
}