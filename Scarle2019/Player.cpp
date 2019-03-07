#include "pch.h"
#include "Player.h"
#include "GameStateData.h"
#include <iostream>

extern void ExitGame();

Player::Player(RenderData* _RD, string _filename, int _playerID, GamePad &_gamePad) : TrackMagnet(_RD, _filename)
{
	SetDrag(0.7);
	SetPhysicsOn(true);
	// SetPhysicsOn(false);
	m_playerID = _playerID;
	m_gamePad = &_gamePad;
}

Player::~Player()
{
	//tidy up anything I've created
}


void Player::Tick(GameStateData* _GSD)
{
	//WORKAROUND TO PREVENT PLAYER MOVEMENT - NEEDS TO BE REMOVED
	if (m_playerID != 1)
	{
		//FORWARD BACK & STRAFE CONTROL HERE
		Vector3 forwardMove = 40.0f * m_world.Forward();
		Vector3 rightMove = 40.0f * m_world.Right();
		Matrix rotMove = Matrix::CreateRotationY(m_yaw);
		forwardMove = Vector3::Transform(forwardMove, rotMove);
		rightMove = Vector3::Transform(rightMove, rotMove);
		//float rotSpeed = 0.05f;


		if (_GSD->m_keyboardState.W)
		{
			m_acc += forwardMove;
		}
		if (_GSD->m_keyboardState.S)
		{
			m_acc -= forwardMove;
		}
		if (_GSD->m_keyboardState.A)
		{
			m_acc -= rightMove;
		}
		if (_GSD->m_keyboardState.D)
		{
			m_acc += rightMove;
		}

		//GameController Movement
		if (_GSD->m_gamePadState[m_playerID].IsConnected())
		{
			if (_GSD->m_gamePadState[m_playerID].IsViewPressed())
			{
				ExitGame();
			}
			else
			{
				if (_GSD->m_gamePadState[m_playerID].IsRightTriggerPressed())
				{
					m_acc += forwardMove * _GSD->m_gamePadState[m_playerID].triggers.right;
				}

				if (_GSD->m_gamePadState[m_playerID].IsLeftTriggerPressed())
				{
					m_acc -= forwardMove; //* _GSD->m_gamePadState->triggers.left;
				}

				if (_GSD->m_gamePadState[m_playerID].IsLeftThumbStickLeft())
				{
					m_acc -= rightMove;// *_GSD->m_gamePadState[m_playerID].buttons.leftStick;
				}

				if (_GSD->m_gamePadState[m_playerID].IsLeftThumbStickRight())
				{
					m_acc += rightMove;// *_GSD->m_gamePadState[m_playerID].buttons.leftStick;
				}
			}
			m_gamePad->SetVibration(m_playerID, _GSD->m_gamePadState[m_playerID].triggers.right * 0.1, _GSD->m_gamePadState[m_playerID].triggers.right * 0.1);
		}

		// Debug code to save/load the players world matrix
		if (m_keymindManager.keyPressed("Debug Save Matrix"))
		{
			m_savedMatrix = m_world;
			m_savedVel = m_vel;
			m_savedGravVel = m_gravVel;
		}
		else if (m_keymindManager.keyPressed("Debug Load Matrix"))
		{
			m_world = m_savedMatrix;
			m_vel = m_savedVel;
			m_gravVel = m_savedGravVel;
			Vector3 scale = Vector3::Zero;
			Quaternion rot = Quaternion::Identity;
			m_world.Decompose(scale, rot, m_pos);
			m_rot = Matrix::CreateFromQuaternion(rot);
		}

		//change orinetation of player
		float rotSpeed = 0.001f;
		m_yaw -= rotSpeed * _GSD->m_mouseState.x;
		m_pitch -= rotSpeed * _GSD->m_mouseState.y;

		m_yaw -= rotSpeed * _GSD->m_gamePadState[m_playerID].thumbSticks.rightX;
		m_pitch += rotSpeed * _GSD->m_gamePadState[m_playerID].thumbSticks.rightY;
	}
	//apply my base behaviour
	PhysModel::Tick(_GSD);

}