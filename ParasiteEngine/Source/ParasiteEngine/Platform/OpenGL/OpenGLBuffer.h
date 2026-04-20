#pragma once
#include "ParasiteEngine/Renderer/Buffer.h"


namespace Parasite
{
	class COpenGLVertexBuffer : public CVertexBuffer
	{
	public:
		COpenGLVertexBuffer(uint32_t InSize);
		COpenGLVertexBuffer(float* InVertices, uint32_t InSize);
		virtual ~COpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* InData, int32_t InSize) override;

		virtual void SetLayout(const CBufferLayout& InBufferLayout) override { Layout = InBufferLayout; };
		virtual const CBufferLayout& GetLayout() const override { return Layout; };

	private:
		uint32_t RendererID;
		CBufferLayout Layout;
	};


	class COpenGLIndexBuffer : public CIndexBuffer
	{
	public:
		COpenGLIndexBuffer(uint32_t* InIndices, uint32_t InCount);
		virtual ~COpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return Count; };

	private:
		uint32_t RendererID;
		uint32_t Count;
	};
}