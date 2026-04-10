#pragma once

#include "memory"
#include "ParasiteEngine/Renderer/Buffer.h"


namespace Parasite
{
	class CVertexArray
	{
	public:
		virtual ~CVertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<CVertexBuffer>& InVertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<CIndexBuffer>& InIndexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<CVertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<CIndexBuffer>& GetIndexBuffer() const = 0;

		static CVertexArray* Create();
	};
}