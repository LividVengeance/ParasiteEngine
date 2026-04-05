#include "pepch.h"

#include "WindowsWindow.h"

#include "ParasiteEngine/Log.h"


namespace Parasite
{
	static bool bIsGLFWInitialized = false;

	CWindow* CWindow::Create(const SWindowInfo& InInfo)
	{
		return new CWindowsWindow(InInfo);
	}

	CWindowsWindow::CWindowsWindow(const SWindowInfo& InInfo)
	{
		Init(InInfo);
	}

	CWindowsWindow::~CWindowsWindow()
	{
		Shutdown();
	}

	void CWindowsWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(Window);
	}
	
	void CWindowsWindow::SetVSyncEnabled(bool bInEnabled)
	{
		glfwSwapInterval(static_cast<int>(bInEnabled));
		WindowData.bVSyncEnabled = bInEnabled;
	}

	void CWindowsWindow::Init(const SWindowInfo& InInfo)
	{
		WindowData = InInfo;

		PE_CORE_LOG("Creating window {0} ({1}, {2})", WindowData.Title, WindowData.Width, WindowData.Height);
	
		if (!bIsGLFWInitialized)
		{
			const int Success = glfwInit();

			PE_CORE_ASSERT(Success, "Failed to init GLFW window");
			bIsGLFWInitialized = true;
		}
	
		Window = glfwCreateWindow(static_cast<int>(WindowData.Width), static_cast<int>(WindowData.Height), WindowData.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(Window);
		glfwSetWindowUserPointer(Window, &WindowData);
		SetVSyncEnabled(true);
	}

	void CWindowsWindow::Shutdown()
	{
		glfwDestroyWindow(Window);
	}
}