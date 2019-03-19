#include "pch.h"
#include "Camera.h"
#include "GameStateData.h"
#include "Player.h"
#include "Keyboard.h"
#include "KeybindManager.h"
#include <math.h>

Camera::Camera(float _width, float _height, float _near, float _far, GameObject3D* _target, Vector3 _dpos)
{
	m_pos = Vector3::Backward;
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f, _width  / _height , _near, _far);
	m_targetObject = _target;
	m_dpos = _dpos;
}

void Camera::Tick()
{
	switch (behav)
	{
	case BEHAVIOUR::BEHIND:
	{
		if (m_targetObject)
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetObject->GetPos(), m_targetObject->GetWorld().Up());
			rotCam = m_targetObject->GetOri();
			m_pos = m_targetObject->GetPos() + m_targetObject->GetPos().Transform(m_dpos, rotCam);
		}
		else
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetPos, Vector3::Up);
		}

		break;
	}
	case BEHAVIOUR::LERP:
	{
		m_dpos = Vector3{ 0.0f, 3.0f, 10.0f };
		if (m_targetObject)
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetObject->GetPos(), m_targetObject->GetWorld().Up());
			if (rotCam != m_targetObject->GetOri())
			{
				rotCam = Matrix::Lerp(rotCam, m_targetObject->GetOri(), 0.1);
			}
			if (m_pos != m_targetObject->GetPos() + m_targetObject->GetPos().Transform(m_dpos, rotCam))
			{
				m_pos = Vector3::Lerp(m_pos, m_targetObject->GetPos() + m_targetObject->GetPos().Transform(m_dpos, rotCam), 0.25);
			}
		}
		else
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetPos, Vector3::Up);
		}

		break;
	}
	case BEHAVIOUR::ORBIT:
	{
		if (m_targetObject)
		{

			m_dpos = Vector3{ 10.0f, 3.0f, 10.0f };
			m_view = Matrix::CreateLookAt(m_pos, m_targetObject->GetPos(), m_targetObject->GetWorld().Up());

			rotCam = m_targetObject->GetOri();
			Vector3 base_pos = m_targetObject->GetPos() + m_targetObject->GetPos().Transform(m_dpos, rotCam);
			angle += 1.0f;
			Vector3 orbit_pos;
			orbit_pos.x = sin(angle / 57.2958f) * (base_pos.x - m_targetObject->GetPos().x);

			orbit_pos.z = cos(angle / 57.2958f) * (base_pos.z - m_targetObject->GetPos().z);

			m_pos = (m_targetObject->GetPos() + m_targetObject->GetPos().Transform({ orbit_pos.x, m_dpos.y, orbit_pos.z }, rotCam));
		}
		else
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetPos, Vector3::Up);
		}
		break;
	}
	case BEHAVIOUR::CINEMATIC:
	{

		if (points.size())
		{

			rotCam = Matrix::Identity;

			if (cam_point != -1)
			{
				m_pos = Vector3::Lerp(points[cam_point][0], points[cam_point][1], timer / time_out);
				m_targetPos = look_points[cam_point];
				timer += Locator::getGSD()->m_dt;
				if (timer >= time_out)
				{
					timer = 0.0f;
					cam_point--;
				}
			}

			if (m_targetObject)
			{
				m_view = Matrix::CreateLookAt(m_pos, m_targetObject->GetPos(), Vector3::Up);
			}
			else
			{
				m_view = Matrix::CreateLookAt(m_pos, m_targetPos, Vector3::Up);
			}
		}
		else
		{
			behav = BEHAVIOUR::ORBIT;
		}

		break;
	}
	case BEHAVIOUR::FRONT:
	{
		if (m_targetObject)
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetObject->GetPos(), m_targetObject->GetWorld().Up());
			rotCam = m_targetObject->GetOri();

			if (m_pos != m_targetObject->GetPos() + m_targetObject->GetPos().Transform(m_dpos, rotCam))
			{
				m_pos = Vector3::Lerp(m_pos, m_targetObject->GetPos() + m_targetObject->GetPos().Transform(m_dpos, rotCam), 0.2);
			}
		}
		break;
	}
	case BEHAVIOUR::FIRST:
	{
		if (m_targetObject)
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetObject->GetPos() + m_targetObject->GetPos().Transform(Vector3{ 0.0f, 0.0f, -10.0f }, rotCam), m_targetObject->GetWorld().Up());

			if (rotCam != m_targetObject->GetOri())
			{
				rotCam = Matrix::Lerp(rotCam, m_targetObject->GetOri(), 0.08);
			}
			if (m_pos != m_targetObject->GetPos() + m_targetObject->GetPos().Transform(Vector3{ 0.0f, 1.0f, -1.0f }, rotCam))
			{
				m_pos = Vector3::Lerp(m_pos, m_targetObject->GetPos() + m_targetObject->GetPos().Transform(Vector3{ 0.0f, 1.0f, -1.0f }, rotCam), 0.8);
			}
		}
		else
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetPos, Vector3::Up);
		}
		break;
	}
	case BEHAVIOUR::INDEPENDENT_LERP:
	{
		m_dpos = Vector3{ 10.0f, 3.0f, 10.0f };
		if (Locator::getGSD()->m_gamePadState[m_cameraID].IsRightThumbStickLeft())
		{
			angle -= 3.0f;// *_GSD->m_gamePadState[m_playerID].buttons.leftStick;
		}

		if (Locator::getGSD()->m_gamePadState[m_cameraID].IsRightThumbStickRight())
		{
			angle += 3.0f;// *_GSD->m_gamePadState[m_playerID].buttons.leftStick;
		}

		if (m_targetObject)
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetObject->GetPos(), m_targetObject->GetWorld().Up());
			rotCam = m_targetObject->GetOri();
			Vector3 base_pos = m_targetObject->GetPos() + m_targetObject->GetPos().Transform(m_dpos, rotCam);
			Vector3 orbit_pos;
			orbit_pos.x = sin(angle / 57.2958f) * (base_pos.x - m_targetObject->GetPos().x);

			orbit_pos.z = cos(angle / 57.2958f) * (base_pos.z - m_targetObject->GetPos().z);

			if (m_pos != (m_targetObject->GetPos() + m_targetObject->GetPos().Transform({ orbit_pos.x, m_dpos.y, orbit_pos.z }, rotCam)))
			{
				m_pos = Vector3::Lerp(m_pos, m_targetObject->GetPos() + m_targetObject->GetPos().Transform({ orbit_pos.x, m_dpos.y, orbit_pos.z }, rotCam), 0.2);
			}
		}
		else
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetPos, Vector3::Up);
			rotCam = m_world;
			Vector3 base_pos = m_targetPos + Vector3::Transform(m_dpos, rotCam);
			Vector3 orbit_pos;
			orbit_pos.x = sin(angle / 57.2958f) * (base_pos.x - m_targetPos.x);

			orbit_pos.z = cos(angle / 57.2958f) * (base_pos.z - m_targetPos.z);

			m_pos = m_targetPos + Vector3::Transform({ orbit_pos.x, m_dpos.y, orbit_pos.z }, rotCam);
			if (m_pos != m_targetPos + Vector3::Transform({ orbit_pos.x, m_dpos.y, orbit_pos.z }, rotCam))
			{
				m_pos = Vector3::Lerp(m_pos, m_targetPos + Vector3::Transform(m_dpos, rotCam), 0.2);
			}
		}
		break;
	}
	case BEHAVIOUR::INDEPENDENT_FIXED:
	{
		m_dpos = Vector3{ 10.0f, 3.0f, 10.0f };
		if (Locator::getGSD()->m_gamePadState[m_cameraID].IsRightThumbStickLeft())
		{
			angle -= 1.0f;// *_GSD->m_gamePadState[m_playerID].buttons.leftStick;
		}

		if (Locator::getGSD()->m_gamePadState[m_cameraID].IsRightThumbStickRight())
		{
			angle += 1.0f;// *_GSD->m_gamePadState[m_playerID].buttons.leftStick;
		}

		if (m_targetObject)
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetObject->GetPos(), m_targetObject->GetWorld().Up());
			rotCam = m_targetObject->GetOri();
			Vector3 base_pos = m_targetObject->GetPos() + m_targetObject->GetPos().Transform(m_dpos, rotCam);
			Vector3 orbit_pos;
			orbit_pos.x = sin(angle / 57.2958f) * (base_pos.x - m_targetObject->GetPos().x);

			orbit_pos.z = cos(angle / 57.2958f) * (base_pos.z - m_targetObject->GetPos().z);

			m_pos = (m_targetObject->GetPos() + m_targetObject->GetPos().Transform({ orbit_pos.x, m_dpos.y, orbit_pos.z }, rotCam));

		}
		else
		{
			m_view = Matrix::CreateLookAt(m_pos, m_targetPos, Vector3::Up);
			rotCam = m_world;
			Vector3 base_pos = m_targetPos + Vector3::Transform(m_dpos, rotCam);
			Vector3 orbit_pos;
			orbit_pos.x = sin(angle / 57.2958f) * (base_pos.x - m_targetObject->GetPos().x);

			orbit_pos.z = cos(angle / 57.2958f) * (base_pos.z - m_targetObject->GetPos().z);

			m_pos = m_targetPos + Vector3::Transform({ orbit_pos.x, m_dpos.y, orbit_pos.z }, rotCam);
		}
		break;
	}
	case BEHAVIOUR::DEBUG_CAM:
	{
		float cam_speed = 40.0f;
		float cam_rot_speed = 0.007f;
		if (m_keybinds.keyHeld("DebugCamSpeedup"))
		{
			cam_speed *= 2;
			cam_rot_speed *= 2;
		}

		Vector3 forwardMove = cam_speed * m_world.Forward();
		Vector3 rightMove = cam_speed * m_world.Right();
		Vector3 upMove = cam_speed * m_world.Up();
		Matrix rotMove = Matrix::CreateRotationY(m_yaw);
		forwardMove = Vector3::Transform(forwardMove, rotMove);
		rightMove = Vector3::Transform(rightMove, rotMove);
		upMove = Vector3::Transform(upMove, rotMove);
		m_targetPos = m_pos + forwardMove;

		m_yaw -= cam_rot_speed * Locator::getGSD()->m_mouseState.x;
		m_pitch -= cam_rot_speed * Locator::getGSD()->m_mouseState.y;

		if (m_keybinds.keyHeld("DebugCamFor"))
		{
			m_pos += Locator::getGSD()->m_dt * forwardMove;
			m_targetPos += Locator::getGSD()->m_dt * forwardMove;
		}
		else if (m_keybinds.keyHeld("DebugCamBack"))
		{
			m_pos -= Locator::getGSD()->m_dt * forwardMove;
			m_targetPos -= Locator::getGSD()->m_dt * forwardMove;
		}

		if (m_keybinds.keyHeld("DebugCamLeft"))
		{
			m_pos -= Locator::getGSD()->m_dt * rightMove;
			m_targetPos -= Locator::getGSD()->m_dt * rightMove;
		}
		else if (m_keybinds.keyHeld("DebugCamRight"))
		{
			m_pos += Locator::getGSD()->m_dt * rightMove;
			m_targetPos += Locator::getGSD()->m_dt * rightMove;
		}

		if (m_keybinds.keyHeld("DebugCamUp"))
		{
			m_pos -= Locator::getGSD()->m_dt * upMove;
			m_targetPos -= Locator::getGSD()->m_dt * upMove;
		}
		else if (m_keybinds.keyHeld("DebugCamDown"))
		{
			m_pos += Locator::getGSD()->m_dt * upMove;
			m_targetPos += Locator::getGSD()->m_dt * upMove;
		}

		m_view = Matrix::CreateLookAt(m_pos, m_targetPos, m_pos.Up);

		break;
	}
	}

	//Debug output player location - useful for setting up spawns
	if (m_keybinds.keyPressed("Debug Print Camera Location")) {
		std::cout << "CAMERA POSITION: (" << m_pos.x << ", " << m_pos.y << ", " << m_pos.z << ")" << std::endl;
	}

	GameObject3D::Tick();
}