#pragma once

#include "ParasiteEngine/Layer.h"'

#include "ParasiteEngine/Events/MouseEvents.h"
#include "ParasiteEngine/Events/KeyEvent.h"
#include "ParasiteEngine/Events/ApplicationEvent.h"


namespace Parasite
{
	class PARASITE_API CImGuiLayer : public CLayer
	{
	public:
		CImGuiLayer();
		~CImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(CEvent& InEvent) override;

	private:
		bool OnMouseButtonPressed(CMousePressedEvent& InEvent);
		bool OnMouseButtonReleased(CMouseReleasedEvent& InEvent);
		bool OnMouseScroll(CMouseScrollEvent& InEvent);
		bool OnMouseMove(CMouseMoveEvent& InEvent);

		bool OnKeyPressedEvent(CPressedKeyEvent& InEvent);
		bool OnKeyReleasedEvent(CReleasedKeyEvent& InEvent);
		bool OnKeyTypedEvent(CTypedKeyEvent& InEvent);
		
		bool OnWindowResize(CWindowResizeEvent& InEvent);

	private:
		float Time = 0.0f;
	};
}