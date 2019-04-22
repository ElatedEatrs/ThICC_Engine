#include "pch.h"
#include "MoveAI.h"
#include <stack>
#include <iostream>

MoveAI::MoveAI(PhysModel* _model, ControlledMovement* _move) : m_model(_model), m_move(_move)
{
	for (int i = 0; i < m_maxPathIterations; i++)
	{
		m_debugRaceLine.push_back(new SDKMeshGO3D("DEFAULT_ITEM"));
		m_debugRaceLine.back()->Load();
		Vector3 new_scale = m_debugRaceLine.back()->GetScale() * ((float)(i+1) / m_maxPathIterations);
		m_debugRaceLine.back()->SetScale(1);
		m_debugRaceLine.back()->UpdateWorld();
	}
	for (int i = 0; i < 20; i++)
	{
		m_debugNextWaypoint.push_back(new SDKMeshGO3D("DEFAULT_ITEM"));
		m_debugNextWaypoint.back()->Load();
		m_debugNextWaypoint.back()->SetScale(0.2f);
		m_debugNextWaypoint.back()->UpdateWorld();
	}
	m_move->SetGamepadActive(false);
}

void MoveAI::DebugRender()
{
	
	for (SDKMeshGO3D* mesh : m_debugRaceLine)
	{
		mesh->Render();
	}
	for (SDKMeshGO3D* mesh : m_debugNextWaypoint)
	{
		//mesh->Render();
	}
}

void MoveAI::Update()
{
	// If there at least 2 waypoints left
	if (m_routeIndex < m_route.size()-1 && !m_route.empty())
	{
		// If close to the current waypoint OR the the Karts current position is closer to the next waypoint than the previous waypoint is
		if (Vector3::Distance(m_model->GetPos(), m_route[m_routeIndex]) <= m_wayPointHitRadius ||
			Vector3::Distance(m_model->GetPos(), m_route[m_routeIndex+1]) < Vector3::Distance(m_route[m_routeIndex], m_route[m_routeIndex + 1]))
		{
			m_routeIndex++;
			// This shouldn't happen often, but if we reach the end of the waypoints don't continue
			if (m_routeIndex == m_route.size())
			{
				return;
			}
		}
	}

	Vector3 normVelo = m_model->getVelocity();
	normVelo.Normalize();
	Vector3 normVeloLeft = normVelo + (m_model->GetWorld().Left() * 0.25f);
	normVeloLeft.Normalize();
	Vector3 normVeloRight = normVelo + (m_model->GetWorld().Right() * 0.25f);
	normVeloRight.Normalize();

	if (m_route.empty())
	{
		m_move->setAcceleration(1);
		return;
	}
	m_move->setAcceleration(1);
	Vector3 normDiff = m_route[m_routeIndex] - m_model->GetPos();
	normDiff.Normalize();
	
	// If the currentl veloicty is too far off the driving line
	float dist = Vector3::Distance(normVelo, normDiff);
	DebugText::print(std::to_string(dist));
	if (dist  > m_lineLeeway)
	{
		// If left would reduce the difference
		if (Vector3::Distance(normVeloLeft, normDiff) < dist)
		{
			m_move->TurnLeft();
		}
		else if (Vector3::Distance(normVeloRight, normDiff) < dist)
		{
			m_move->TurnRight();
		}
	}
	else
	{
		m_move->DontTurn();
	}
}

void MoveAI::RecalculateLine(Track* _track)
{
	m_routeIndex = 0;
	_track->SetValidCollision(true, false, true, false);
	m_route.clear();
	Matrix world = m_model->GetWorld();
	Vector3 pos = m_model->GetPos();
	Vector3 direction = world.Forward();
	int iterations = 0;

	m_waypointPos = m_move->GetWaypoint();

	Vector3 diff = _track->getWaypointMiddle(m_waypointPos) - pos;
	diff = diff * (1.0f / m_debugNextWaypoint.size());
	for (int i = 0; i < m_debugNextWaypoint.size(); i++)
	{
		m_debugNextWaypoint[i]->SetPos(pos + (i*diff));
		m_debugNextWaypoint[i]->UpdateWorld();
	}

	FindRoute(_track, world, pos, direction, iterations, true, m_waypointPos);

	if (m_route.size() < 3)
	{
		return;
	}
	// Loop through the route and remove nodes that are roughly on the same line
	Vector3 previous_direction = m_route[1] - m_route[0];
	Vector3 total_deflection = Vector3::Zero;
	std::vector<Vector> condensedRoute;
	for (int i = 1; i < m_route.size()-1; i++)
	{
		// Find the deflection from the previous direction and add it to the total
		Vector3 new_direction = m_route[i+1] - m_route[i];
		total_deflection += new_direction - previous_direction;
		// If the acculated deflection gets too high
		if (total_deflection.Length() > m_deflectionLimit)
		{
			// Add the current node to the new vector and set the previous direction as the new one
			total_deflection = Vector3::Zero;
			condensedRoute.push_back(m_route[i]);
			previous_direction = new_direction;
		}
	}
	
	for (int i = 0; i < m_route.size(); i++)
	{
		m_debugRaceLine[i]->SetShouldRender(true);
		m_debugRaceLine[i]->SetPos(m_route[i]);
		m_debugRaceLine[i]->UpdateWorld();
	}
	for (int i = m_route.size(); i < m_debugRaceLine.size(); i++)
	{
		m_debugRaceLine[i]->SetShouldRender(false);
	}

	condensedRoute.push_back(m_route.back());
	m_route = condensedRoute;



}

bool MoveAI::FindRoute(Track* _track, Matrix& _world, Vector3& _pos, Vector3& _direction, int _iterations, bool _allowTurn, int _waypointIndex)
{
	while (_iterations < m_maxPathIterations)
	{
		Matrix newWorld = Matrix::Identity;
		Vector3 newPos = Vector::Zero;
		
		// Check to see if straight ahead is valid
		int count = FindWorld(_track, _world, newWorld, _pos, newPos, _direction, m_minFrontSpace, _iterations, _waypointIndex);
		// If straight ahead isn't valid
		if (count < m_minFrontSpace)
		{
			// Try left and right recurring this method to find a valid route
			if (_allowTurn)
			{
				Vector right;
				Vector left;
				if (count < m_minFrontSpace / 2)
				{
					right = _world.Right();
					left = _world.Left();
				}
				else
				{
					right = _world.Right() + _world.Forward();
					left = _world.Left() + _world.Forward();
					right.Normalize();
					left.Normalize();
				}
				if (FindRoute(_track, _world, _pos, right, _iterations, false, _waypointIndex))
				{
					return true;
				}
				else
				{
					m_route.resize(_iterations);
				}

				return(FindRoute(_track, _world, _pos, left, _iterations, false, _waypointIndex));
			}
			// Return straight away if this is the first iteration, this prevents going down a pointless tree
			else
			{
				return false;
			}
		}
		// If straight ahead is valid
		else
		{
			// Find the world forward of this one
			FindWorld(_track, _world, newWorld, _pos, newPos, _direction, 1, _iterations, _waypointIndex);
			_world = newWorld;
			_pos = newPos;
			_direction = _world.Forward();
			_iterations++;
			_allowTurn = true;
			m_route.push_back(_pos);
		}
	}
	return true;
}

int MoveAI::FindWorld(Track* _track, const Matrix& _startWorld, Matrix& _endWorld, const Vector3& _startPos, Vector3& _endPos, Vector3 _direction, const int& _steps, const int& _iteration, int &_waypointIndex)
{
	_direction *= m_aiPathStep;

	// Check to see if this direction diverges from the waypoint
	float diff = Vector3::DistanceSquared(_startPos, _track->getWaypointMiddle(_waypointIndex)) - Vector3::DistanceSquared(_startPos + _direction, _track->getWaypointMiddle(_waypointIndex));
	// If diff is negative they are diverging. So if they are diverging by more than half the step
	if (_iteration > 0 && diff < 0)
	{
		// Check to see if we are also divering from the next waypoint
		if (Vector3::DistanceSquared(_startPos, _track->getWaypointMiddle(_waypointIndex+1)) > Vector3::DistanceSquared(_startPos + _direction, _track->getWaypointMiddle(_waypointIndex+1)))
		{
			// If not, use this waypoint instead of the current one
			_waypointIndex++;
		}
		else
		{
			// Otherwise this direction is in-valid
			return 0;
		}
	}

	Vector3 intersect = Vector3::Zero;
	MeshTri* tri = nullptr;

	_endWorld = _startWorld;
	_endPos = _startPos;

	for (int i = 0; i < _steps; i++)
	{
		if (_track->DoesLineIntersect(_endWorld.Down()*(m_model->data.m_height * 10), _endPos + (_endWorld.Up() * (m_model->data.m_height * 2)), intersect, tri, 0.4f))
		{
			// If there is a valid collision, find the new world ahead on the track
			Vector secondIntersect;
			MeshTri* tri2 = nullptr;
			tri->DoesLineIntersect(_endWorld.Down() * (m_model->data.m_height * 10), _endPos + _direction + (_endWorld.Up() * (m_model->data.m_height * 2)), secondIntersect, tri2, 0.4f);

			_endWorld = Matrix::CreateWorld(secondIntersect, secondIntersect - intersect, tri->m_plane.Normal());
			_direction = _endWorld.Forward() * m_aiPathStep;

			Vector scale = Vector::Zero;
			Quaternion rot = Quaternion::Identity;
			_endWorld.Decompose(scale, rot, _endPos);
		}
		else
		{
			return i;
		}
	}
	return _steps;
}