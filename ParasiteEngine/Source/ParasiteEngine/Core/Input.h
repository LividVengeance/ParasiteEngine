#pragma once
#include "Core.h"


namespace Parasite
{
	class PARASITE_API CInput
	{
	public:
		inline static bool IsKeyPressed(int InKeyCode) { return Instance->IsKeyPressedImpl(InKeyCode); }
		
		inline static bool IsMousePressed(int InButton) { return Instance->IsMousePressedImpl(InButton); }
		inline static float GetMouseX() { return Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return Instance->GetMouseYImpl(); }
		inline static std::pair<float, float> GetMousePosition() { return Instance->GetMousePositionImpl(); }
	
	protected:
		virtual bool IsKeyPressedImpl(int InKeyCode) = 0;

		virtual bool IsMousePressedImpl(int InButton) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static CInput* Instance;
	};
}