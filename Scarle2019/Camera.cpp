#include "pch.h"
#include "Camera.h"


Camera::Camera(float _width, float _height, float _near, float _far, GameObject3D* _target, Vector3 _dpos)
{
	m_pos = Vector3::Backward;
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f, _width / _height, _near, _far);
	m_targetObject = _target;
	m_dpos = _dpos;
}


Camera::~Camera()
{
}

void Camera::Tick(GameStateData* _GSD)
{
	if (enabled)
	{
		if (m_targetObject)
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetObject->GetPos(), Vector3::Up);
			Matrix rotCam = Matrix::CreateFromYawPitchRoll(m_targetObject->GetYaw(), 0.0f, 0.0f);
			m_pos = m_targetObject->GetPos() + Vector3::Transform(m_dpos, rotCam);
		}
		else
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetPos, Vector3::Up);
		}
	}

	GameObject3D::Tick(_GSD);
}

void Camera::setDeltaPos(Vector3 _dpos)
{
	m_dpos = _dpos;
}

void Camera::Enable(bool val)
{
	enabled = val;
}
