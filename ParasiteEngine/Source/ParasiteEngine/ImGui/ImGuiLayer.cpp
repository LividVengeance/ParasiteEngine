#include "pepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "ParasiteEngine/Application.h"

// temp: to remove
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_opengl3_loader.h"


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
		glClear(GL_COLOR_BUFFER_BIT);

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
		CEventDispatcher EventDispatcher(InEvent);
		EventDispatcher.Dispatch<CMousePressedEvent>(PE_BIND_EVENT_FUNC(CImGuiLayer::OnMouseButtonPressed));
		EventDispatcher.Dispatch<CMouseReleasedEvent>(PE_BIND_EVENT_FUNC(CImGuiLayer::OnMouseButtonReleased));
		EventDispatcher.Dispatch<CMouseScrollEvent>(PE_BIND_EVENT_FUNC(CImGuiLayer::OnMouseScroll));
		EventDispatcher.Dispatch<CMouseMoveEvent>(PE_BIND_EVENT_FUNC(CImGuiLayer::OnMouseMove));
		
		EventDispatcher.Dispatch<CPressedKeyEvent>(PE_BIND_EVENT_FUNC(CImGuiLayer::OnKeyPressedEvent));
		EventDispatcher.Dispatch<CReleasedKeyEvent>(PE_BIND_EVENT_FUNC(CImGuiLayer::OnKeyReleasedEvent));
		EventDispatcher.Dispatch<CTypedKeyEvent>(PE_BIND_EVENT_FUNC(CImGuiLayer::OnKeyTypedEvent));
		
		EventDispatcher.Dispatch<CWindowResizeEvent>(PE_BIND_EVENT_FUNC(CImGuiLayer::OnWindowResize));
	}

	bool CImGuiLayer::OnMouseButtonPressed(CMousePressedEvent& InEvent)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.MouseDown[InEvent.GetMouseButton()] = true;

		return false;
	}

	bool CImGuiLayer::OnMouseButtonReleased(CMouseReleasedEvent& InEvent)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.MouseDown[InEvent.GetMouseButton()] = false;

		return false;
	}

	bool CImGuiLayer::OnMouseScroll(CMouseScrollEvent& InEvent)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.MouseWheelH += InEvent.GetXOffset();
		IO.MouseWheel += InEvent.GetYOffset();

		return false;
	}

	bool CImGuiLayer::OnMouseMove(CMouseMoveEvent& InEvent)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.MousePos = ImVec2(InEvent.GetX(), InEvent.GetY());

		return false;
	}

	bool CImGuiLayer::OnKeyPressedEvent(CPressedKeyEvent& InEvent)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.KeysData[InEvent.GetKeyCode()].Down = true;

		IO.KeyCtrl = IO.KeysData[GLFW_KEY_LEFT_CONTROL].Down || IO.KeysData[GLFW_KEY_RIGHT_CONTROL].Down;
		IO.KeyShift = IO.KeysData[GLFW_KEY_LEFT_SHIFT].Down || IO.KeysData[GLFW_KEY_RIGHT_SHIFT].Down;
		IO.KeyAlt = IO.KeysData[GLFW_KEY_LEFT_ALT].Down || IO.KeysData[GLFW_KEY_RIGHT_ALT].Down;
		IO.KeySuper = IO.KeysData[GLFW_KEY_LEFT_SUPER].Down || IO.KeysData[GLFW_KEY_RIGHT_SUPER].Down;

		return false;
	}

	bool CImGuiLayer::OnKeyReleasedEvent(CReleasedKeyEvent& InEvent)
	{
		return false;
	}

	bool CImGuiLayer::OnKeyTypedEvent(CTypedKeyEvent& InEvent)
	{
		ImGuiIO& IO = ImGui::GetIO();
		const int KeyCode = InEvent.GetKeyCode();

		if (KeyCode > 0 && KeyCode < 0x10000)
		{
			IO.AddInputCharacter(static_cast<unsigned short>(KeyCode));
		}

		return false;
	}

	bool CImGuiLayer::OnWindowResize(CWindowResizeEvent& InEvent)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.DisplaySize = ImVec2(static_cast<float>(InEvent.GetWidth()), static_cast<float>(InEvent.GetHeight()));
		IO.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, InEvent.GetWidth(), InEvent.GetHeight());

		return false;
	}
}