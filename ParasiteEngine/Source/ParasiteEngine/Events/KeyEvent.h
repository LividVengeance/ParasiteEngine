#pragma once

#include "ParasiteEngine/Events/Event.h"
#include "ParasiteEngine/Core.h"


namespace Parasite
{
	class PARASITE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return KeyCode; }

		EVENT_CLASS_CATEGORY(CategoryInput | CategoryKeyboard)

	protected:
		KeyEvent(int InKeyCode)
			: KeyCode(InKeyCode)
		{
		}

	protected:
		int KeyCode;
	};


	class PARASITE_API PressedKeyEvent : public KeyEvent
	{
	public:
		PressedKeyEvent(int InKeyCode, int InRepeatCount)
			: KeyEvent(InKeyCode),
				RepeatCount(InRepeatCount)
		{
		}

		inline int GetRepeatCount() const { return RepeatCount; }

		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "Pressed Key Event| Repeat count : " << GetRepeatCount();
			return SS.str();
		}

		EVENT_CLASS_CATEGORY(CategoryKeyPressed);

	private:
		int RepeatCount = 0;
	};


	class PARASITE_API ReleasedKeyEvent : public KeyEvent
	{
	public:
		ReleasedKeyEvent(int InKeyCode)
			: KeyEvent(InKeyCode)
		{
		}

		virtual std::string ToString() const override
		{
			return "Released Key Event";
		}

		EVENT_CLASS_CATEGORY(CategoryKeyReleased);
	};
}