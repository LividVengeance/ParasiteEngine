#pragma once


namespace Parasite
{
	class CGraphicContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
};