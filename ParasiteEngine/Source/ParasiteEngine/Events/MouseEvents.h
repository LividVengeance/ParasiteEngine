#pragma once

#include "ParasiteEngine/Events/Event.h"
#include "ParasiteEngine/Core.h"


namespace Parasite
{
	class PARASITE_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float InX, float InY)
			: MouseX(InX),
				MouseY(InY)
		{
		}

		inline float GetX() const { return MouseX; }
		inline float GetY() const { return MouseY; }

		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "Mouse Move Event: " << GetX() << ", " << GetY();
			return SS.str();
		}

		EVENT_CLASS_TYPE(MouseMove);
		EVENT_CLASS_CATEGORY(CategoryInput | CategoryMouse);
	
	private:
		float MouseX, MouseY;
	};


	class PARASITE_API MouseScrollEvent : public Event
	{
		MouseScrollEvent(float InXOffset, float InYOffset)
			: XOffset(InXOffset),
				YOffset(InYOffset)
		{
		}

		inline float GetXOffset() const { return XOffset; }
		inline float GetYOffset() const { return YOffset; }

		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "Mouse Scroll Event: " << GetXOffset() << ", " << GetYOffset();
			return SS.str();
		}

		EVENT_CLASS_TYPE(MouseScroll);
		EVENT_CLASS_CATEGORY(CategoryInput | CategoryMouse);

	private:
		float XOffset, YOffset;
	};


	class PARASITE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return Button; }

		EVENT_CLASS_CATEGORY(CategoryInput | CategoryMouse)

	protected:
		MouseButtonEvent(int InButton)
			: Button(InButton)
		{
		}

	protected:
		int Button;
	};


	class PARASITE_API MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(int InButton)
			: MouseButtonEvent(InButton)
		{
		}

		virtual std::string ToString() const override
		{
			return "Mouse Pressed Event";
		}

		EVENT_CLASS_TYPE(MousePressed);
	};


	class PARASITE_API MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(int InButton)
			: MouseButtonEvent(InButton)
		{
		}

		virtual std::string ToString() const override
		{
			return "Mouse Released Event";
		}

		EVENT_CLASS_TYPE(MouseReleased);
	};
}