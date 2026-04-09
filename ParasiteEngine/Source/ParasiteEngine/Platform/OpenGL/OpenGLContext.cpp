#include "pepch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "Glad/glad.h"


namespace Parasite
{
	COpenGLContext::COpenGLContext(GLFWwindow* InWindowHandle)
		: WindowHandle(InWindowHandle)
	{
		PE_CORE_ASSERT(WindowHandle, "No valid window handle.");
	}

	void COpenGLContext::Init()
	{
		glfwMakeContextCurrent(WindowHandle);
		const int Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PE_CORE_ASSERT(Status, "Failed to initalize Glad");

		PE_CORE_INFO("OpenGL Renderer: {0}", (const char*)glGetString(GL_VENDOR));
	}

	void COpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(WindowHandle);
	}
}