#pragma once
#include "ParasiteEngine/Input.h"

namespace Parasite
{
	class CWindowsInput : public CInput
	{
	protected:
		virtual bool IsKeyPressedImpl(int InKeyCode) override;

		virtual bool IsMousePressedImpl(int InButton) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}