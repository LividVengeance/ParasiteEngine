#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"

namespace Parasite
{
	class CRenderCommand
	{
	public:
		inline static void Init()
		{
			RendererAPI->Init();
		}

		inline static void SetViewport(uint32_t InX, uint32_t InY, uint32_t InWidth, uint32_t InHeight)
		{
			RendererAPI->SetViewport(InX, InY, InWidth, InHeight);
		}

		inline static void DrawIndexed(const TSharedPtr<CVertexArray>& InVertexArray)
		{
			RendererAPI->DrawIndexed(InVertexArray);
		}

		inline static void SetClearColour(const glm::vec4& InColour)
		{
			RendererAPI->SetClearColour(InColour);
		}

		inline static void Clear()
		{
			RendererAPI->Clear();
		}

	private:
		static CRendererAPI* RendererAPI;
	};
}