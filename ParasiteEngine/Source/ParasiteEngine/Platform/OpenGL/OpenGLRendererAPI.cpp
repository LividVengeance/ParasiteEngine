#include "pepch.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"


namespace Parasite
{
	void COpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void COpenGLRendererAPI::SetViewport(uint32_t InX, uint32_t InY, uint32_t InWidth, uint32_t InHeight)
	{
		glViewport(InX, InY, InWidth, InHeight);
	}

	void COpenGLRendererAPI::SetClearColour(const glm::vec4& InColour)
	{
		glClearColor(InColour.r, InColour.g, InColour.b, InColour.a);
	}

	void COpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void COpenGLRendererAPI::DrawIndexed(const TSharedPtr<CVertexArray>& InVertexArray)
	{
		glDrawElements(GL_TRIANGLES, InVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}