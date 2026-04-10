#pragma once


namespace Parasite
{
	enum class ERendererAPI
	{
		None = 0,
		OpenGL,
	};


	class CRenderer
	{
	public:
		inline static ERendererAPI GetRendererAPI() { return RendererAPI; }

	private:
		static ERendererAPI RendererAPI;
	};
}
