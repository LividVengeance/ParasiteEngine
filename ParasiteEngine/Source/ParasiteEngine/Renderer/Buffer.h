#pragma once

namespace Parasite
{
	enum class EShaderDataType : uint8_t
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool,
	};

	static uint32_t ShaderDataTypeSize(EShaderDataType InType)
	{
		switch (InType)
		{
			case Parasite::EShaderDataType::Float:		return 4;
			case Parasite::EShaderDataType::Float2:		return 4 * 2;
			case Parasite::EShaderDataType::Float3:		return 4 * 3;
			case Parasite::EShaderDataType::Float4:		return 4 * 4;
			case Parasite::EShaderDataType::Mat3:		return 4 * 3 * 3;
			case Parasite::EShaderDataType::Mat4:		return 4 * 4 * 4;
			case Parasite::EShaderDataType::Int:		return 4;
			case Parasite::EShaderDataType::Int2:		return 4 * 2;
			case Parasite::EShaderDataType::Int3:		return 4 * 3;
			case Parasite::EShaderDataType::Int4:		return 4 * 4;
			case Parasite::EShaderDataType::Bool:		return 1;
		}

		PE_ASSERT(false, "Failed to find shader data type.");
		return 0;
	}

	struct SBufferElement
	{
	public:
		SBufferElement() {}
		SBufferElement(EShaderDataType InType, const std::string& InName, bool bInNormalized = false)
			: Type(InType), Name(InName), Size(ShaderDataTypeSize(InType)), Offset(0), bNormalized(bInNormalized)
		{
		}

		const uint32_t GetComponentCount() const 
		{ 
			switch (Type)
			{
				case Parasite::EShaderDataType::Float:		return 1;
				case Parasite::EShaderDataType::Float2:		return 2;
				case Parasite::EShaderDataType::Float3:		return 3;
				case Parasite::EShaderDataType::Float4:		return 4;
				case Parasite::EShaderDataType::Mat3:		return 3 * 3;
				case Parasite::EShaderDataType::Mat4:		return 4 * 4;
				case Parasite::EShaderDataType::Int:		return 1;
				case Parasite::EShaderDataType::Int2:		return 2;
				case Parasite::EShaderDataType::Int3:		return 3;
				case Parasite::EShaderDataType::Int4:		return 4;
				case Parasite::EShaderDataType::Bool:		return 1;
			}

			PE_ASSERT(false, "Failed to get component count for type.");
			return 0;
		}

	public:
		std::string Name;
		EShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool bNormalized;
	};


	class CBufferLayout
	{
	public:
		CBufferLayout() {}
		CBufferLayout(const std::initializer_list<SBufferElement>& InElements)
			: Elements(InElements)
		{
			CalculateOffsetAndStride();
		}


		inline uint32_t GetStride() const { return Stride; }
		inline const std::vector<SBufferElement>& GetElements() const { return Elements; }

		std::vector<SBufferElement>::iterator begin() { return Elements.begin(); }
		std::vector<SBufferElement>::iterator end() { return Elements.end(); }
		std::vector<SBufferElement>::const_iterator begin() const { return Elements.begin(); }
		std::vector<SBufferElement>::const_iterator end() const { return Elements.end(); }
	
	private:
		void CalculateOffsetAndStride();

	private:
		std::vector<SBufferElement> Elements;
		uint32_t Stride = 0;
	};


	class CVertexBuffer
	{
	public:
		virtual ~CVertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const CBufferLayout& InBufferLayout) = 0;
		virtual const CBufferLayout& GetLayout() const = 0;

		static CVertexBuffer* Create(float* InVertices, uint32_t InSize);
	};


	class CIndexBuffer
	{
	public:
		virtual ~CIndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static CIndexBuffer* Create(uint32_t* InIndices, uint32_t InCount);
	};
}