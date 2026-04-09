#include "pepch.h"
#include "Application.h"

#include "ParasiteEngine/Events/Event.h"
#include "ParasiteEngine/Log.h"
#include "ParasiteEngine/KeyCodes.h"

#include "Glad/glad.h"

#include "Input.h"


namespace Parasite
{
	CApplication* CApplication::Instance = nullptr;

	CApplication::CApplication()
	{
		PE_CORE_ASSERT(!Instance, "An Application already exists.");
		Instance = this;

		Window = std::unique_ptr<CWindow>(CWindow::Create());
		Window->SetEventCallback(std::bind(&CApplication::OnEvent, this, std::placeholders::_1));
	
		ImGuiLayer = new CImGuiLayer();
		PushOverlay(ImGuiLayer);

		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);

		glGenBuffers(1, &VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

		float Vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f, 0.5f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

		unsigned int Indices[3] =
		{
			0, 1, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Run()
	{
		while (bRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (CLayer* Layer : LayerStack)
			{
				Layer->OnUpdate();
			}

			ImGuiLayer->Begin();
			for (CLayer* Layer : LayerStack)
			{
				Layer->OnImGuiRender();
			}
			ImGuiLayer->End();

			if (Parasite::CInput::IsKeyPressed(PE_KEY_A))
			{
				PE_CORE_LOG("Pressed A!");
			}

			Window->Update();
		}
	}

	void CApplication::OnEvent(CEvent& InEvent)
	{
		CEventDispatcher EventDispatcher(InEvent);
		EventDispatcher.Dispatch<CWindowCloseEvent>(std::bind(&CApplication::OnWindowClose, this, std::placeholders::_1));
	
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