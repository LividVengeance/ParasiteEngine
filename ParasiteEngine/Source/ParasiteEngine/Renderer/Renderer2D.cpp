#include "pepch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "glm/ext/matrix_transform.hpp"


namespace Parasite
{
	struct SQuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Colour;
		glm::vec2 TexCoord;
	};

	struct SRenderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		TSharedPtr<CVertexArray> QuadVertexArray;
		TSharedPtr<CVertexBuffer> QuadVertexBuffer;
		TSharedPtr<CShader> TextureShader;
		TSharedPtr<CTexture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		SQuadVertex* QuadVertexBufferBase = nullptr;
		SQuadVertex* QuadVertexBufferPtr = nullptr;
	};
	static SRenderer2DData Data;


	void CRenderer2D::Init()
	{
		Data.QuadVertexArray = CVertexArray::Create();

		Data.QuadVertexBuffer = CVertexBuffer::Create(Data.MaxVertices  * sizeof(SQuadVertex));
		Data.QuadVertexBuffer->SetLayout(
			{
				{ EShaderDataType::Float3, "a_Position" },
				{ EShaderDataType::Float4, "a_Colour" },
				{ EShaderDataType::Float2, "a_TexCoord" },
			}
		);
		Data.QuadVertexArray->AddVertexBuffer(Data.QuadVertexBuffer);

		Data.QuadVertexBufferBase = new SQuadVertex[Data.MaxVertices];

		uint32_t* QuadIndices = new uint32_t[Data.MaxIndices];

		uint32_t Offset = 0;
		for (uint32_t Index = 0; Index < Data.MaxIndices; Index += 6)
		{
			QuadIndices[Index + 0] = Offset + 0;
			QuadIndices[Index + 1] = Offset + 1;
			QuadIndices[Index + 2] = Offset + 2;

			QuadIndices[Index + 3] = Offset + 2;
			QuadIndices[Index + 4] = Offset + 3;
			QuadIndices[Index + 5] = Offset + 0;

			Offset += 4;
		}

		TSharedPtr<CIndexBuffer> QuadIndexBuffer = CIndexBuffer::Create(QuadIndices, Data.MaxIndices);
		Data.QuadVertexArray->SetIndexBuffer(QuadIndexBuffer);
		delete[] QuadIndices;

		Data.WhiteTexture = CTexture2D::Create(1, 1);
		uint32_t TextureData = 0xffffffff;
		Data.WhiteTexture->SetData(&TextureData, sizeof(TextureData));

		Data.TextureShader = CShader::Create("Assets/Shaders/Texture.glsl");
		Data.TextureShader->Bind();
		Data.TextureShader->SetInt("u_Texture", 0);
	}

	void CRenderer2D::Shutdown()
	{
	}

	void CRenderer2D::BeginScene(const CCamera& InCamera)
	{
		Data.TextureShader->Bind();
		Data.TextureShader->SetMat4("u_ViewProjection", InCamera.GetViewProjectionMatrix());

		Data.QuadIndexCount = 0;
		Data.QuadVertexBufferPtr = Data.QuadVertexBufferBase;
	}

	void CRenderer2D::EndScene()
	{
		uint32_t DataSize = static_cast<uint32_t>(Data.QuadVertexBufferPtr - Data.QuadVertexBufferBase) * sizeof(SQuadVertex);
		Data.QuadVertexBuffer->SetData(Data.QuadVertexBufferBase, DataSize);
		Flush();
	}

	void CRenderer2D::Flush()
	{
		CRenderCommand::DrawIndexed(Data.QuadVertexArray, Data.QuadIndexCount);
	}

	void CRenderer2D::DrawQuad(const glm::vec2& InPosition, const glm::vec2& InSize, const glm::vec4 InColour)
	{
		DrawQuad({ InPosition.x, InPosition.y, 0.0f }, InSize, InColour);
	}

	void CRenderer2D::DrawQuad(const glm::vec3& InPosition, const glm::vec2& InSize, const glm::vec4 InColour)
	{
		Data.QuadVertexBufferPtr->Position = InPosition;
		Data.QuadVertexBufferPtr->Colour = InColour;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = { InPosition.x + InSize.x, InPosition.y, 0.0f };
		Data.QuadVertexBufferPtr->Colour = InColour;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = { InPosition.x + InSize.x, InPosition.y + InSize.y, 0.0f };
		Data.QuadVertexBufferPtr->Colour = InColour;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = { InPosition.x, InPosition.y + InSize.y, 0.0f };;
		Data.QuadVertexBufferPtr->Colour = InColour;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;

		//Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		//Data.WhiteTexture->Bind();
		//
		//glm::mat4 Transform = glm::translate(glm::mat4(1.0f), InPosition) 
		//	* glm::scale(glm::mat4(1.0f), {InSize.x, InSize.y, 1.0f});
		//Data.TextureShader->SetMat4("u_Transform", Transform);
		//
		//Data.QuadVertexArray->Bind();
		//CRenderCommand::DrawIndexed(Data.QuadVertexArray);
	}

	void CRenderer2D::DrawQuad(const glm::vec2& InPosition, const glm::vec2& InSize, const TSharedPtr<CTexture>& InTexture, const float InTilingFactor, const glm::vec4& InTintColour)
	{
		DrawQuad({ InPosition.x, InPosition.y, 0.0f }, InSize, InTexture, InTilingFactor, InTintColour);
	}

	void CRenderer2D::DrawQuad(const glm::vec3& InPosition, const glm::vec2& InSize, const TSharedPtr<CTexture>& InTexture, const float InTilingFactor, const glm::vec4& InTintColour)
	{
		Data.TextureShader->SetFloat4("u_Colour", InTintColour);
		Data.TextureShader->SetFloat("u_TilingFactor", InTilingFactor);
		Data.TextureShader->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), InPosition) 
			* glm::scale(glm::mat4(1.0f), { InSize.x, InSize.y, 1.0f });
		Data.TextureShader->SetMat4("u_Transform", Transform);

		InTexture->Bind();

		Data.QuadVertexArray->Bind();
		CRenderCommand::DrawIndexed(Data.QuadVertexArray);
	}

	void CRenderer2D::DrawRotatedQuad(const glm::vec3& InPosition, const glm::vec2& InSize, const float InRotation, const glm::vec4 InColour)
	{
		Data.TextureShader->SetFloat4("u_Colour", InColour);
		Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		Data.WhiteTexture->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), InPosition) 
			* glm::rotate(glm::mat4(1.0f), InRotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { InSize.x, InSize.y, 1.0f });
		Data.TextureShader->SetMat4("u_Transform", Transform);

		Data.QuadVertexArray->Bind();
		CRenderCommand::DrawIndexed(Data.QuadVertexArray);
	}

	void CRenderer2D::DrawRotatedQuad(const glm::vec3& InPosition, const glm::vec2& InSize, const float InRotation, const TSharedPtr<CTexture>& InTexture, const float InTilingFactor, const glm::vec4& InTintColour)
	{
		Data.TextureShader->SetFloat4("u_Colour", InTintColour);
		Data.TextureShader->SetFloat("u_TilingFactor", InTilingFactor);
		Data.TextureShader->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), InPosition)
			* glm::rotate(glm::mat4(1.0f), InRotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { InSize.x, InSize.y, 1.0f });
		Data.TextureShader->SetMat4("u_Transform", Transform);

		InTexture->Bind();

		Data.QuadVertexArray->Bind();
		CRenderCommand::DrawIndexed(Data.QuadVertexArray);
	}
}