#include "pepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "ParasiteEngine/Platform/OpenGL/OpenGLShader.h"


namespace Parasite
{
	TSharedPtr<CShader> CShader::Create(const std::string& InFilePath)
	{
		switch (CRenderer::GetRendererAPI())
		{
			case CRendererAPI::EAPI::None: return nullptr;
			case CRendererAPI::EAPI::OpenGL: return std::make_shared<COpenGLShader>(InFilePath);
		}
		return nullptr;
	}
	
	TSharedPtr<CShader> CShader::Create(const std::string& InName, const std::string& InVertexSource, const std::string& InFragmentSource)
	{
		switch (CRenderer::GetRendererAPI())
		{
			case CRendererAPI::EAPI::None: return nullptr;
			case CRendererAPI::EAPI::OpenGL: return make_shared<COpenGLShader>(InName, InVertexSource, InFragmentSource);
		}
		return nullptr;
	}


	void CShaderLibirary::Add(const std::string& InName, const TSharedPtr<CShader>& InShader)
	{
		PE_CORE_ASSERT(!Shaders.contains(InName), "Shader of same name has already been added.");
		Shaders[InName] = InShader;
	}

	void CShaderLibirary::Add(const TSharedPtr<CShader>& InShader)
	{
		const std::string& ShaderName = InShader->GetName();
		Add(ShaderName, InShader);
	}

	TSharedPtr<CShader> CShaderLibirary::Load(const std::string& InFilepath)
	{
		TSharedPtr<CShader> Shader = CShader::Create(InFilepath);
		Add(Shader);
		return Shader;
	}

	TSharedPtr<CShader> CShaderLibirary::Load(const std::string& InName, const std::string& InFilepath)
	{
		TSharedPtr<CShader> Shader = CShader::Create(InFilepath);
		Add(InName, Shader);
		return Shader;
	}

	TSharedPtr<CShader> CShaderLibirary::Load(const std::string& InName, const std::string& InVertexSource, const std::string& InFragmentSource)
	{
		TSharedPtr<CShader> Shader = CShader::Create(InName, InVertexSource, InFragmentSource);
		Add(InName, Shader);
		return Shader;
	}

	TSharedPtr<CShader> CShaderLibirary::Get(const std::string& InName)
	{
		PE_CORE_ASSERT(Shaders.contains(InName), "Shader of name has not been added to library.");
		return Shaders[InName];
	}
}