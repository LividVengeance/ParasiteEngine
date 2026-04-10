#pragma once

#include "Core.h"
#include "Window.h"
#include "ParasiteEngine/Events/ApplicationEvent.h"
#include "ParasiteEngine/LayerStack.h"
#include "ParasiteEngine/ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h" // todo: remove
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"


namespace Parasite
{
	class PARASITE_API CApplication
	{
	public:
		CApplication();
		virtual ~CApplication();

		void Run();
		void OnEvent(CEvent& InEvent);

		void PushLayer(CLayer* InLayer);
		void PushOverlay(CLayer* InOverlay);

		inline static CApplication& Get() { return *Instance; }
		inline CWindow& GetWindow() { return *Window; }

	private:
		bool OnWindowClose(CWindowCloseEvent& InWindowCloseEvent);

	private:
		CLayerStack LayerStack;

		std::unique_ptr<CWindow> Window;
		CImGuiLayer* ImGuiLayer;
		bool bRunning = true;

		std::shared_ptr<CShader> Shader;
		std::shared_ptr<CVertexArray> VertexArray;

		std::shared_ptr<CShader> BlueShader;
		std::shared_ptr<CVertexArray> SquareVertexArray;
		
		static CApplication* Instance;
	};

	// To be defined in client
	CApplication* CreateApplication();
}