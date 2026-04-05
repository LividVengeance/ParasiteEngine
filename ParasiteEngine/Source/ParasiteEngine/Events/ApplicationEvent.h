#pragma once

#include "ParasiteEngine/Events/Event.h"


namespace Parasite
{
	class PARASITE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int InWindowWidth, unsigned int InWindowHeight)
			: WindowWidth(InWindowWidth),
			  WindowHeight(InWindowHeight)
		{
		}

		inline unsigned int GetWidth() const { return WindowWidth; }
		inline unsigned int GetHeight() const { return WindowHeight; }

		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "Window Resize Event: " << GetWidth() << ", " << GetHeight();
			return SS.str();
		}

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(CategoryApplication);
	private:
		unsigned int WindowWidth, WindowHeight;
	};
}