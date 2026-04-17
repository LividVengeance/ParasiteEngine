#include "pepch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"
#include "ParasiteEngine/Core/Application.h"


namespace Parasite
{
	CInput* CInput::Instance = new CWindowsInput();

	bool CWindowsInput::IsKeyPressedImpl(int InKeyCode)
	{
		GLFWwindow* Window = static_cast<GLFWwindow*>(CApplication::Get().GetWindow().GetNativeWindow());
		int State = glfwGetKey(Window, InKeyCode);
		return State == GLFW_PRESS || State == GLFW_REPEAT;
	}

	bool CWindowsInput::IsMousePressedImpl(int InButton)
	{
		GLFWwindow* Window = static_cast<GLFWwindow*>(CApplication::Get().GetWindow().GetNativeWindow());
		int State = glfwGetMouseButton(Window, InButton);
		return State == GLFW_PRESS;
	}

	std::pair<float, float> CWindowsInput::GetMousePositionImpl()
	{
		double MouseX, MouseY;
		GLFWwindow* Window = static_cast<GLFWwindow*>(CApplication::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(Window, &MouseX, &MouseY);
		return { static_cast<float>(MouseX), static_cast<float>(MouseY) };
	}

	float CWindowsInput::GetMouseXImpl()
	{
		auto [XPos, YPos] = GetMousePositionImpl();
		return XPos;
	}

	float CWindowsInput::GetMouseYImpl()
	{
		auto [XPos, YPos] = GetMousePositionImpl();
		return YPos;
	}
}