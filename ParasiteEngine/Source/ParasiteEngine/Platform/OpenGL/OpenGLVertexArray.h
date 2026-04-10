#pragma once
#include "ParasiteEngine/Renderer/VertexArray.h"


namespace Parasite
{
	class COpenGLVertexArray : public CVertexArray
	{
	public:
		COpenGLVertexArray();
		virtual ~COpenGLVertexArray() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<CVertexBuffer>& InVertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<CIndexBuffer>& InIndexBuffer) override;
	
		virtual const std::vector<std::shared_ptr<CVertexBuffer>>& GetVertexBuffers() const { return VertexBuffers; }
		virtual const std::shared_ptr<CIndexBuffer>& GetIndexBuffer() const { return IndexBuffer; };

	private:
		uint32_t RendererID;

		std::vector<std::shared_ptr<CVertexBuffer>> VertexBuffers;
		std::shared_ptr<CIndexBuffer> IndexBuffer;
	};
}