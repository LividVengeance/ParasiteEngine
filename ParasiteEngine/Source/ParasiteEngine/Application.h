#pragma once

#include "Core.h"
#include "Window.h"

namespace Parasite
{
	class PARASITE_API CApplication
	{
	public:
		CApplication();
		virtual ~CApplication();

		void Run();

	private:
		std::unique_ptr<CWindow> Window;
		bool bRunning = true;
	};

	// To be defined in client
	CApplication* CreateApplication();
}