#include "pepch.h"
#include "Application.h"

#include "ParasiteEngine/Events/ApplicationEvent.h"
#include "ParasiteEngine/Log.h"

#include "GLFW/glfw3.h"

namespace Parasite
{
	CApplication::CApplication()
	{
		Window = std::unique_ptr<CWindow>(CWindow::Create());
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Run()
	{
		while (bRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			Window->Update();
		}
	}
}