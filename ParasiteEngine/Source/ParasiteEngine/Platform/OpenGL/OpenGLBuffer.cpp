#include "pepch.h"
#include "OpenGLBuffer.h"

#include "Glad/glad.h"


namespace Parasite
{
	////////////////////////////////////////////////////////////////////////////////
	///	Vertex Buffer //////////////////////////////////////////////////////////////

	COpenGLVertexBuffer::COpenGLVertexBuffer(float* InVertices, uint32_t InSize)
	{
		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ARRAY_BUFFER, InSize, InVertices, GL_STATIC_DRAW);
	}

	COpenGLVertexBuffer::~COpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &RendererID);
	}

	void COpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
	}

	void COpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	////////////////////////////////////////////////////////////////////////////////
	///	Index Buffer ///////////////////////////////////////////////////////////////

	COpenGLIndexBuffer::COpenGLIndexBuffer(uint32_t* InIndices, uint32_t InCount)
		:	Count(InCount)
	{
		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, InCount * sizeof(uint32_t), InIndices, GL_STATIC_DRAW);
	}

	COpenGLIndexBuffer::~COpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &RendererID);
	}

	void COpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
	}

	void COpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}