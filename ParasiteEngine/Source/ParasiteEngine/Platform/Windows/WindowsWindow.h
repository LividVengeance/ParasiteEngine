#pragma once

#include "ParasiteEngine/Window.h"
#include "ParasiteEngine/Core.h"

#include "GLFW/glfw3.h"

#include "ParasiteEngine/Renderer/GraphicContext.h"


namespace Parasite
{
	class PARASITE_API CWindowsWindow : public CWindow
	{
	public:
		CWindowsWindow(const SWindowInfo& InInfo);
		virtual ~CWindowsWindow() override;

		virtual void Update() override;

		virtual unsigned int GetWidth() const override { return WindowData.Width; };
		virtual unsigned int GetHeight() const override { return WindowData.Height; };

		virtual void SetEventCallback(const EventCallbackFunc& InCallbackFunc) override { WindowData.EventCallback = InCallbackFunc; };
		virtual void SetVSyncEnabled(bool bInEnabled) override;
		virtual bool IsVSyncEnabled() const override { return WindowData.bVSyncEnabled; };

		inline virtual void* GetNativeWindow() const override { return Window; }

	private:
		void Init(const SWindowInfo& InInfo);
		void Shutdown();

	private:
		GLFWwindow* Window;
		CGraphicContext* Context;

		struct SWindowData
		{
			SWindowData() = default;
			SWindowData(const SWindowInfo& InInfo)
			{
				Width = InInfo.Width;
				Height = InInfo.Height;
				Title = InInfo.Title;
			}

			unsigned int Width;
			unsigned int Height;
			std::string Title;

			bool bVSyncEnabled = true;

			EventCallbackFunc EventCallback;
		};

		SWindowData WindowData;
	};
}