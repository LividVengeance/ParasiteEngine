#include "pepch.h"
#include "Application.h"

#include "ParasiteEngine/Events/Event.h"
#include "ParasiteEngine/Log.h"
#include "ParasiteEngine/KeyCodes.h"

#include "Glad/glad.h"

#include "Input.h"


namespace Parasite
{
	CApplication* CApplication::Instance = nullptr;

	CApplication::CApplication()
	{
		PE_CORE_ASSERT(!Instance, "An Application already exists.");
		Instance = this;

		Window = std::unique_ptr<CWindow>(CWindow::Create());
		Window->SetEventCallback(std::bind(&CApplication::OnEvent, this, std::placeholders::_1));

		ImGuiLayer = new CImGuiLayer();
		PushOverlay(ImGuiLayer);
		
		VertexArray.reset(CVertexArray::Create());

		float Vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f,			0.8f, 0.2f, 0.8f, 1.f,
			 0.5f, -0.5f, 0.0f,			0.2f, 0.3f, 0.8f, 1.f,
			 0.0f, 0.5f, 0.0f,			0.8f, 0.8f, 0.2f, 1.f,
		};

		std::shared_ptr<CVertexBuffer> VertexBuffer;
		VertexBuffer.reset(CVertexBuffer::Create(Vertices, sizeof(Vertices)));
		CBufferLayout BufferLayout = 
		{
			{ EShaderDataType::Float3, "a_Position" },
			{ EShaderDataType::Float4, "a_Color" },
		};
		VertexBuffer->SetLayout(BufferLayout);
		VertexArray->AddVertexBuffer(VertexBuffer);

		uint32_t Indices[3] = { 0, 1, 2 };
		std::shared_ptr<CIndexBuffer> IndexBuffer;
		IndexBuffer.reset(CIndexBuffer::Create(Indices, 3));
		VertexArray->SetIndexBuffer(IndexBuffer);

		SquareVertexArray.reset(CVertexArray::Create());

		float SquareVertices[3 * 4] =
		{
			-0.75f,		-0.75f, 0.0f,
			 0.75f,		-0.75f, 0.0f,
			 0.75f,		 0.75f, 0.0f,
			-0.75f,		 0.75f, 0.0f,
		};

		std::shared_ptr<CVertexBuffer> SquareVertexBuffer;
		SquareVertexBuffer.reset(CVertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		SquareVertexBuffer->SetLayout({
				{ EShaderDataType::Float3, "a_Position" },
		});
		SquareVertexArray->AddVertexBuffer(SquareVertexBuffer);

		uint32_t SqaureIndices[6] = { 0, 1, 2, 2, 3, 0};
		std::shared_ptr<CIndexBuffer> SqaureIndexBuffer;
		SqaureIndexBuffer.reset(CIndexBuffer::Create(SqaureIndices, sizeof(SqaureIndices) / sizeof(uint32_t)));
		SquareVertexArray->SetIndexBuffer(SqaureIndexBuffer);

		std::string VertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string FragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position* 0.5 + 0.5, 1.0);
				color = v_Color;	
			}
		)";

		std::string VertexSource2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string FragmentSource2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);	
			}
		)";

		Shader.reset(new CShader(VertexSource, FragmentSource));
		BlueShader.reset(new CShader(VertexSource2, FragmentSource2));
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Run()
	{
		while (bRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			BlueShader->Bind();
			SquareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			Shader->Bind();
			VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (CLayer* Layer : LayerStack)
			{
				Layer->OnUpdate();
			}

			ImGuiLayer->Begin();
			for (CLayer* Layer : LayerStack)
			{
				Layer->OnImGuiRender();
			}
			ImGuiLayer->End();

			Window->Update();
		}
	}

	void CApplication::OnEvent(CEvent& InEvent)
	{
		CEventDispatcher EventDispatcher(InEvent);
		EventDispatcher.Dispatch<CWindowCloseEvent>(std::bind(&CApplication::OnWindowClose, this, std::placeholders::_1));

		for (auto It = LayerStack.end(); It != LayerStack.begin(); )
		{
			if (CLayer* Layer = *--It)
			{
				Layer->OnEvent(InEvent);
				if (InEvent.IsHandled())
				{
					break;
				}
			}
		}
	}

	void CApplication::PushLayer(CLayer* InLayer)
	{
		LayerStack.PushLayer(InLayer);
	}

	void CApplication::PushOverlay(CLayer* InOverlay)
	{
		LayerStack.PushOverlay(InOverlay);
	}

	bool CApplication::OnWindowClose(CWindowCloseEvent& InWindowCloseEvent)
	{
		bRunning = false;
		return true;
	}
}