#pragma once
#include "Camera.h"
#include "Texture.h"


namespace Parasite
{
	class CRenderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		
		static void BeginScene(const CCamera& InCamera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& InPosition, const glm::vec2& InSize, const glm::vec4 InColour);
		static void DrawQuad(const glm::vec3& InPosition, const glm::vec2& InSize, const glm::vec4 InColour);
		static void DrawQuad(const glm::vec2& InPosition, const glm::vec2& InSize, const TSharedPtr<CTexture>& InTexture);
		static void DrawQuad(const glm::vec3& InPosition, const glm::vec2& InSize, const TSharedPtr<CTexture>& InTexture);
	};
}