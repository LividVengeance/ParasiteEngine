#include "pepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "ParasiteEngine/Application.h"
#include "GLFW/glfw3.h"


namespace Parasite
{

	CImGuiLayer::CImGuiLayer()
		: CLayer("ImGuiLayer")
	{
	}

	CImGuiLayer::~CImGuiLayer()
	{

	}

	void CImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		
		ImGuiIO& IO = ImGui::GetIO();
		IO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		IO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void CImGuiLayer::OnDetach()
	{

	}

	void CImGuiLayer::OnUpdate()
	{
		ImGuiIO& IO = ImGui::GetIO();
		CApplication& Application = CApplication::Get();

		IO.DisplaySize = ImVec2((float)Application.GetWindow().GetWidth(), (float)Application.GetWindow().GetHeight());

		float Delta = static_cast<float>(glfwGetTime());
		IO.DeltaTime = Time > 0.0f ? (Delta - Time) : (1.0f / 60.0f);
		Time = Delta;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool Show = true;
		ImGui::ShowDemoWindow(&Show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void CImGuiLayer::OnEvent(CEvent& InEvent)
	{

	}
}