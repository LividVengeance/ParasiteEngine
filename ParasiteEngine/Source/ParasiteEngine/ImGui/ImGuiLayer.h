#pragma once

#include "ParasiteEngine/Layer.h"

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
		float Time = 0.0f;
	};
}