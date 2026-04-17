#include "pepch.h"
#include "Renderer.h"
#include "RenderCommand.h"

#include "ParasiteEngine/Platform/OpenGL/OpenGLShader.h"


namespace Parasite
{
	CRenderer::SSceneData* CRenderer::SceneData = new CRenderer::SSceneData();

	void CRenderer::Init()
	{
		CRenderCommand::Init();
	}

	void CRenderer::OnWindowResize(uint32_t InWidth, uint32_t InHeight)
	{
		CRenderCommand::SetViewport(0, 0, InWidth, InHeight);
	}

	void CRenderer::BeginScene(CCamera& InCamera)
	{
		SceneData->ViewProjectionMatrix = InCamera.GetViewProjectionMatrix();
	}

	void CRenderer::EndScene()
	{

	}

	void CRenderer::Submit(const TSharedPtr<CShader> InShader, const TSharedPtr<CVertexArray>& InVertexArray, const glm::mat4& InTransform)
	{
		InShader->Bind();
		std::dynamic_pointer_cast<COpenGLShader>(InShader)->UploadUniformMat4("u_ViewProjection", SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<COpenGLShader>(InShader)->UploadUniformMat4("u_Transform", InTransform);

		InVertexArray->Bind();
		CRenderCommand::DrawIndexed(InVertexArray);
	}
}