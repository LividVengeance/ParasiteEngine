#include "pepch.h"
#include "OpenGLTexture.h"

#include "GLAD/glad.h"
#include "stb_image.h"


namespace Parasite
{
	COpenGLTexture2D::COpenGLTexture2D(const std::string& InPath)
		: Path(InPath)
	{
		int LoadedWidth, LoadedHeight, Channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* Data = stbi_load(Path.c_str(), &LoadedWidth, &LoadedHeight, &Channels, 0);
		PE_CORE_ASSERT(Data, "Failed to load image.");

		Width = LoadedWidth;
		Height = LoadedHeight;

		GLenum OpenGLFormat, DataFormat = 0;
		if (Channels == 4)
		{
			OpenGLFormat = GL_RGBA8;
			DataFormat = GL_RGBA;
		}
		else if (Channels == 3)
		{
			OpenGLFormat = GL_RGB8;
			DataFormat = GL_RGB;
		}
		else
		{
			PE_CORE_ASSERT(false, "Format not supported.");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &RendererID);
		glTextureStorage2D(RendererID, 1, OpenGLFormat, Width, Height);

		glTextureParameteri(RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(RendererID, 0, 0, 0, Width, Height, DataFormat, GL_UNSIGNED_BYTE, Data);

		stbi_image_free(Data);
	}

	COpenGLTexture2D::~COpenGLTexture2D()
	{
		glDeleteTextures(1, &RendererID);
	}

	void COpenGLTexture2D::Bind(uint32_t InSlot) const
	{
		glBindTextureUnit(InSlot, RendererID);
	}
}