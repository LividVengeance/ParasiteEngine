#include "pepch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "glm/ext/matrix_transform.hpp"


namespace Parasite
{
	struct SRenderer2DData
	{
		TSharedPtr<CVertexArray> QuadVertexArray;
		TSharedPtr<CShader> FlatColourShader;
		TSharedPtr<CShader> TextureShader;
	};
	static SRenderer2DData* Data;


	void CRenderer2D::Init()
	{
		Data = new SRenderer2DData();

		Data->QuadVertexArray = CVertexArray::Create();

		float SquareVertices[5 * 4] =
		{
			-0.5f,-0.5f, 0.0f,		0.0f, 0.0f,
			 0.5f,-0.5f, 0.0f,		1.0f, 0.0f,
			 0.5f, 0.5f, 0.0f,		1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,
		};

		TSharedPtr<CVertexBuffer> SquareVertexBuffer;
		SquareVertexBuffer.reset(CVertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		SquareVertexBuffer->SetLayout(
			{
				{ EShaderDataType::Float3, "a_Position" },
				{ EShaderDataType::Float2, "a_TexCoord" },
			}
		);
		Data->QuadVertexArray->AddVertexBuffer(SquareVertexBuffer);

		uint32_t SqaureIndices[6] = { 0, 1, 2, 2, 3, 0 };
		TSharedPtr<CIndexBuffer> SqaureIndexBuffer;
		SqaureIndexBuffer.reset(CIndexBuffer::Create(SqaureIndices, sizeof(SqaureIndices) / sizeof(uint32_t)));
		Data->QuadVertexArray->SetIndexBuffer(SqaureIndexBuffer);

		Data->FlatColourShader = CShader::Create("Assets/Shaders/FlatColour.glsl");
		Data->TextureShader = CShader::Create("Assets/Shaders/Texture.glsl");
		Data->TextureShader->Bind();
		Data->TextureShader->SetInt("u_Texture", 0);
	}

	void CRenderer2D::Shutdown()
	{
		delete Data;
	}

	void CRenderer2D::BeginScene(const CCamera& InCamera)
	{
		Data->FlatColourShader->Bind();
		Data->FlatColourShader->SetMat4("u_ViewProjection", InCamera.GetViewProjectionMatrix());

		Data->TextureShader->Bind();
		Data->TextureShader->SetMat4("u_ViewProjection", InCamera.GetViewProjectionMatrix());
	}

	void CRenderer2D::EndScene()
	{

	}

	void CRenderer2D::DrawQuad(const glm::vec2& InPosition, const glm::vec2& InSize, const glm::vec4 InColour)
	{
		DrawQuad({ InPosition.x, InPosition.y, 0.0f }, InSize, InColour);
	}

	void CRenderer2D::DrawQuad(const glm::vec3& InPosition, const glm::vec2& InSize, const glm::vec4 InColour)
	{
		Data->FlatColourShader->Bind();
		Data->FlatColourShader->SetFloat4("u_Colour", InColour);

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), InPosition) * glm::scale(glm::mat4(1.0f), {InSize.x, InSize.y, 1.0f});
		Data->FlatColourShader->SetMat4("u_Transform", Transform);

		Data->QuadVertexArray->Bind();
		CRenderCommand::DrawIndexed(Data->QuadVertexArray);
	}

	void CRenderer2D::DrawQuad(const glm::vec2& InPosition, const glm::vec2& InSize, const TSharedPtr<CTexture>& InTexture)
	{
		DrawQuad({ InPosition.x, InPosition.y, 0.0f }, InSize, InTexture);
	}

	void CRenderer2D::DrawQuad(const glm::vec3& InPosition, const glm::vec2& InSize, const TSharedPtr<CTexture>& InTexture)
	{
		Data->TextureShader->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), InPosition) * glm::scale(glm::mat4(1.0f), { InSize.x, InSize.y, 1.0f });
		Data->TextureShader->SetMat4("u_Transform", Transform);

		InTexture->Bind();

		Data->QuadVertexArray->Bind();
		CRenderCommand::DrawIndexed(Data->QuadVertexArray);
	}
}