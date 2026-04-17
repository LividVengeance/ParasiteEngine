#pragma once
#include "ParasiteEngine/Renderer/RendererAPI.h"


namespace Parasite
{
	class COpenGLRendererAPI : public CRendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetViewport(uint32_t InX, uint32_t InY, uint32_t InWidth, uint32_t InHeight) override;

		virtual void SetClearColour(const glm::vec4& InColour) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const TSharedPtr<CVertexArray>& InVertexArray) override;
	};
}