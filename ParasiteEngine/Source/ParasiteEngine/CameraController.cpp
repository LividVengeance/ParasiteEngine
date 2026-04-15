#include "pepch.h"
#include "CameraController.h"

#include "Input.h"
#include "KeyCodes.h"
#include "Core.h"


namespace Parasite
{
	COrthographicCameraController::COrthographicCameraController(float InAspectRatio, bool bInEnableRotation)
		: Camera(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel),
			AspectRatio(InAspectRatio), bRotationEnabled(bInEnableRotation)
	{
	}

	void COrthographicCameraController::OnUpdate(CTimestep InTimestep)
	{
		if (CInput::IsKeyPressed(PE_KEY_A))
		{
			CameraPosition.x -= GetCameraMoveSpeed(InTimestep);
		}
		if (CInput::IsKeyPressed(PE_KEY_D))
		{
			CameraPosition.x += GetCameraMoveSpeed(InTimestep);
		}
		if (CInput::IsKeyPressed(PE_KEY_W))
		{
			CameraPosition.y += GetCameraMoveSpeed(InTimestep);
		}
		if (CInput::IsKeyPressed(PE_KEY_S))
		{
			CameraPosition.y -= GetCameraMoveSpeed(InTimestep);
		}

		if (bRotationEnabled)
		{
			if (CInput::IsKeyPressed(PE_KEY_Q))
			{
				CameraRotation -= GetCameraRotationSpeed(InTimestep);
			}
			if (CInput::IsKeyPressed(PE_KEY_E))
			{
				CameraRotation += GetCameraRotationSpeed(InTimestep);
			}
		}

		Camera.SetPosition(CameraPosition);
		Camera.SetRotation(CameraRotation);

		CameraTranslationSpeed = ZoomLevel;
	}

	void COrthographicCameraController::OnEvent(CEvent& InEvent)
	{
		CEventDispatcher EventDispatcher(InEvent);
		EventDispatcher.Dispatch<CMouseScrollEvent>(PE_BIND_EVENT_FUNC(COrthographicCameraController::OnMouseScrolledEvent));
		EventDispatcher.Dispatch<CWindowResizeEvent>(PE_BIND_EVENT_FUNC(COrthographicCameraController::OnWindowResize));
	}

	bool COrthographicCameraController::OnMouseScrolledEvent(CMouseScrollEvent& InEvent)
	{
		ZoomLevel -= InEvent.GetYOffset();
		ZoomLevel = std::max(ZoomLevel, 0.25f);
		Camera.SetProjection(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel);
		return false;
	}

	bool COrthographicCameraController::OnWindowResize(CWindowResizeEvent& InEvent)
	{
		AspectRatio = static_cast<float>(InEvent.GetWidth()) / static_cast<float>(InEvent.GetHeight());
		Camera.SetProjection(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel);
		return false;
	}

	float COrthographicCameraController::GetCameraMoveSpeed(CTimestep InTimestep) const
	{
		return CameraTranslationSpeed * InTimestep;
	}

	float COrthographicCameraController::GetCameraRotationSpeed(CTimestep InTimestep) const
	{
		return CameraRotationSpeed * InTimestep;
	}
}