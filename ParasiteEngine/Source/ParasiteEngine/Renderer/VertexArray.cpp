#include "pepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "ParasiteEngine/Platform/OpenGL/OpenGLVertexArray.h"


namespace Parasite
{
	TSharedPtr<CVertexArray> CVertexArray::Create()
	{
		switch (CRenderer::GetRendererAPI())
		{
			case CRendererAPI::EAPI::None: return nullptr;
			case CRendererAPI::EAPI::OpenGL: return std::make_shared<COpenGLVertexArray>();
		}
		return nullptr;
	}
}