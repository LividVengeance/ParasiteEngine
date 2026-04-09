#pragma once

#include "ParasiteEngine/Renderer/GraphicContext.h"

// Forward Declares
struct GLFWwindow;


namespace Parasite
{
	class COpenGLContext : public CGraphicContext
	{
	public:
		COpenGLContext(GLFWwindow* InWindowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* WindowHandle;
	};
}