#include "pepch.h"
#include "Application.h"

#include "ParasiteEngine/Log.h"
#include "Events/Event.h"

#include "Glad/glad.h"


namespace Parasite
{
	CApplication* CApplication::Instance = nullptr;

	CApplication::CApplication()
	{
		PE_CORE_ASSERT(!Instance, "An Application already exists.");
		Instance = this;

		Window = std::unique_ptr<CWindow>(CWindow::Create());
		Window->SetEventCallback(std::bind(&CApplication::OnEvent, this, std::placeholders::_1));
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Run()
	{
		while (bRunning)
		{
			for (CLayer* Layer : LayerStack)
			{
				Layer->OnUpdate();
			}

			Window->Update();
		}
	}

	void CApplication::OnEvent(CEvent& InEvent)
	{
		CEventDispatcher EventDispatcher(InEvent);
		EventDispatcher.Dispatch<CWindowCloseEvent>(std::bind(&CApplication::OnWindowClose, this, std::placeholders::_1));

		PE_CORE_LOG("Event: {}", InEvent.ToString());
	
		for (auto It = LayerStack.end(); It != LayerStack.begin(); )
		{
			if (CLayer * Layer = *--It)
			{
				Layer->OnEvent(InEvent);
				if (InEvent.IsHandled())
				{
					break;
				}
			}
		}
	}

	void CApplication::PushLayer(CLayer* InLayer)
	{
		LayerStack.PushLayer(InLayer);
	}

	void CApplication::PushOverlay(CLayer* InOverlay)
	{
		LayerStack.PushOverlay(InOverlay);
	}

	bool CApplication::OnWindowClose(CWindowCloseEvent& InWindowCloseEvent)
	{
		bRunning = false;
		return true;
	}
}