#pragma once
#include "Track.h"
#include "pch.h"
#include <iostream>
#include <fstream>
#include "math.h"

Track::Track(RenderData* _RD, string _filename) : PhysModel(_RD, _filename)
{
	//Read in track config
	std::ifstream i(m_filepath.generateConfigFilepath(_filename, m_filepath.MODEL));
	json m_track_data_j;
	m_track_data_j << i;

	//Parse loaded config
	m_track_data.scale = m_track_data_j["modelscale"];
	m_track_data.spawn_pos = Vector3(m_track_data_j["start_x"], m_track_data_j["start_y"], m_track_data_j["start_z"]);
	m_track_data.spawn_pos = m_track_data.spawn_pos * m_track_data.scale;
	m_track_data.start_rot = Vector3(m_track_data_j["rot_x"], m_track_data_j["rot_y"], m_track_data_j["rot_z"]); //Hmm, allow this? Will mess with collision.
	m_triSegSize = m_track_data_j["segment_size"];

	//Parse loaded arrays from config
	for (json::iterator it = m_track_data_j["map_waypoints"].begin(); it != m_track_data_j["map_waypoints"].end(); ++it) {
		map_waypoints.push_back(Vector3(it.value()[0], it.value()[1], it.value()[2]));
	}
	for (json::iterator it = m_track_data_j["map_cameras"].begin(); it != m_track_data_j["map_cameras"].end(); ++it) {
		map_cams_pos.push_back(Vector3(it.value()["pos"][0], it.value()["pos"][1], it.value()["pos"][2]));
		map_cams_rot.push_back(Vector3(it.value()["rotation"][0], it.value()["rotation"][1], it.value()["rotation"][2]));
	}
	for (json::iterator it = m_track_data_j["map_spawnpoints"].begin(); it != m_track_data_j["map_spawnpoints"].end(); ++it) {
		map_spawnpoints.push_back(Vector3(it.value()[0], it.value()[1], it.value()[2]));
	}

	//Set our config in action
	SetScale(m_track_data.scale);
	SetRotationInDegrees(m_track_data.start_rot);

	//Debug output
	std::cout << "Loaded track data: " << m_track_data_j["asset_name"] << std::endl;
	std::cout << "Suitable spawn spot: " << m_track_data.spawn_pos.x << ", " << m_track_data.spawn_pos.y << ", " << m_track_data.spawn_pos.z << std::endl;

	//Load track vertex list for generating our collmap
	LoadVertexList(m_filepath.generateFilepath(_filename, m_filepath.MODEL_COLLMAP));

}

/* Returns a suitable spawn location for a player in this map */
Vector3 Track::getSuitableSpawnSpot() {
	return m_track_data.spawn_pos;
}

/* Takes the list of vertices generated by the model tool, and creates a vector of MeshTri's with it */
void Track::LoadVertexList(string _vertex_list)
{
	std::ifstream file(_vertex_list);
	string line;

	// Read all of the vertices from file and build the triangles they make
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			CreateAndAddTriangle(line);
		}
	}
	SplitTrisIntoGrid();
}

/* Takes a line from the file and extract a triangle out of it */
void Track::CreateAndAddTriangle(string _line)
{
	Vector vectors[3];
	string value = "";
	int vectorIndex = 0;

	for (char& c : _line)
	{
		if (c == '(' || c == ' ' || (value == "" && c == ','))
		{
			continue;
		}
		else if (c == ')')
		{
			vectors[vectorIndex] = CreateVector(value);
			vectors[vectorIndex] = vectors[vectorIndex] * m_track_data.scale;
			CompareVectorToMaximum(vectors[vectorIndex]);
			CompareVectorToMinimum(vectors[vectorIndex]);
			vectorIndex++;
			value = "";
			// Once 3 vectors have been found, create a triangle
			if (vectorIndex == 3)
			{
				m_triangles.push_back(MeshTri(vectors[0], vectors[1], vectors[2]));
				vectorIndex = 0;
			}
		}
		else
		{
			value += c;
		}
	}
}

/* Takes a part from the file and extracts the Vector it represents out */
Vector Track::CreateVector(string _vector)
{
	string value = "";
	float values[3];
	int pointIndex = 0;

	for (char& c : _vector)
	{
		// Once a comma is hit, thats the end of this value
		if (c == ',')
		{
			values[pointIndex] = std::stof(value);
			value = "";
			pointIndex++;
		}
		else
		{
			value += c;
		}
	}
	values[2] = std::stof(value);
	return Vector(values[0], values[1], values[2]);
}

/* Sets up the bounding boxes for each waypoint */
void Track::setWaypointBB()
{
	for (size_t i = 0; i < map_waypoints.size() / 2; ++i)
	{
		waypoint_bb.push_back(BoundingBox());
		waypoint_bb[i].Center = { static_cast<float>(map_waypoints[i][0]), static_cast<float>(map_waypoints[i][2]), static_cast<float>(map_waypoints[i][1] * -1) };
		waypoint_bb[i].Extents = { 5, 5, 5 };
	}
}

/* Checks through all triangles to see if this line intersects any of them.
   The point of intersecion is stored in _intersect */
bool Track::DoesLineIntersect(Vector _direction, Vector _startPos, Vector& _intersect, MeshTri*& _tri, float _maxAngle)
{
	// Find the bounding box created by _startPos and _startPos + _direction
	Vector endPos = _startPos + _direction;
	Vector upper = Vector(_startPos.x > endPos.x ? _startPos.x : endPos.x,
						  _startPos.y > endPos.y ? _startPos.y : endPos.y,
						  _startPos.z > endPos.z ? _startPos.z : endPos.z);
	Vector lower = Vector(_startPos.x < endPos.x ? _startPos.x : endPos.x,
					      _startPos.y < endPos.y ? _startPos.y : endPos.y,
					      _startPos.z < endPos.z ? _startPos.z : endPos.z);
	GetXYZIndexAtPoint(upper);
	GetXYZIndexAtPoint(lower);
	
	// Then check all the grid sections covered by this area
	MeshTri* closestTri = nullptr;
	float bestDist = 100000;
	Vector closestIntersect = Vector::Zero;
	for (int i = lower.z; i <= upper.z; i++)
	{
		for (int j = lower.y; j <= upper.y; j++)
		{
			int index = (i*m_triGridYX) + (j*m_triGridX);
			for (int k = lower.x; k <= upper.x; k++)
			{
				for (MeshTri* tri : m_triGrid[index+k])
				{
					if (tri->DoesLineIntersect(_direction, _startPos, _intersect, _tri, _maxAngle))
					{
						float dist = Vector::Distance(_startPos, _intersect);
						if (dist < bestDist)
						{
							closestIntersect = _intersect;
							bestDist = dist;
							closestTri = _tri;
						}
					}
				}
			}
		}
	}
	if (closestTri)
	{
		_intersect = closestIntersect;
		_tri = closestTri;
		return true;
	}
	else
	{
		return false;
	}
}

/* Compares the passed vector to the maximum vector member variable, then updates x, y, z if any are bigger */
void Track::CompareVectorToMaximum(Vector& _vect)
{
	if (_vect.x > m_largest.x)
	{
		m_largest.x = _vect.x;
	}
	if (_vect.y > m_largest.y)
	{
		m_largest.y = _vect.y;
	}
	if (_vect.z > m_largest.z)
	{
		m_largest.z = _vect.z;
	}
}

/* Compares the passed vector to the minimum vector member variable, then updates x, y, z if any are smaller */
void Track::CompareVectorToMinimum(Vector& _vect)
{
	if (_vect.x < m_smallest.x)
	{
		m_smallest.x = _vect.x;
	}
	if (_vect.y < m_smallest.y)
	{
		m_smallest.y = _vect.y;
	}
	if (_vect.z < m_smallest.z)
	{
		m_smallest.z = _vect.z;
	}
}

/* Takes the vector of triangles and creates a vector of vectors of references that are 
ordered by position and grouped into a grid space (defined by m_triSegSize) */
void Track::SplitTrisIntoGrid()
{
	Vector trackSize = m_largest - m_smallest;
	// Reserve space in the references vector based on the size of the track
	m_triGridX = static_cast<int>(ceilf(trackSize.x / m_triSegSize));
	m_triGridY = static_cast<int>(ceilf(trackSize.y / m_triSegSize));
	float m_triGridZ = static_cast<int>(ceilf(trackSize.z / m_triSegSize));
	m_triGridYX = m_triGridY*m_triGridX;
	m_triGrid.reserve(m_triGridX*m_triGridY*m_triGridZ);
	
	for (int i = 0; i < m_triGrid.capacity(); i++)
	{
		std::vector<MeshTri*> vec;
		m_triGrid.push_back(vec);
	}

	for (MeshTri& tri : m_triangles)
	{
		Vector upper = tri.GetUpperBound();
		Vector lower = tri.GetLowerBound();
		GetXYZIndexAtPoint(upper);
		GetXYZIndexAtPoint(lower);

		for (int i = lower.z; i <= upper.z; i++)
		{
			for (int j = lower.y; j <= upper.y; j++)
			{
				int index = (i*m_triGridYX) + (j*m_triGridX);
				for (int k = lower.x; k <= upper.x; k++)
				{
					m_triGrid[index + k].push_back(&tri);
				}
			}
		}
	}

	std::cout << "Track tri map created with " << m_triGridX*m_triGridY*m_triGridZ << " segments";
}

/* Loops though the m_trianges vector and finds every tri that falls within the area at _index  */
void Track::SetAllTrisForIndex(int _index)
{
	Vector startVec = GetAreaAtIndex(_index);
	Vector endVec = startVec + Vector(m_triSegSize, m_triSegSize, m_triSegSize);

	for (MeshTri& tri : m_triangles)
	{
		if (IsPointInBounds(tri.m_pointA, startVec, endVec) ||
			IsPointInBounds(tri.m_pointB, startVec, endVec) ||
			IsPointInBounds(tri.m_pointC, startVec, endVec))
		{
			m_triGrid[_index].push_back(&tri);
		}
	}
}

/* Returns the bottom corner for the grid section this _index represents */
Vector Track::GetAreaAtIndex(int _index)
{
	Vector returnVec = Vector3::Zero;
	returnVec.z = m_triSegSize * floorf(_index / m_triGridYX);
	_index = _index % m_triGridYX;
	returnVec.y = m_triSegSize * floorf(_index / m_triGridX);
	_index = _index % m_triGridX;
	returnVec.x = m_triSegSize * _index;

	return returnVec + m_smallest;
}

/* Returns true is the passed point is inside the bounding box create by _lowerBound and _upperBound */
bool Track::IsPointInBounds(Vector& _point, Vector& _lowerBound, Vector& _upperBound)
{
	return (((_point.x >= _lowerBound.x) && (_point.x <= _upperBound.x)) &&
		((_point.y >= _lowerBound.y) && (_point.y <= _upperBound.y)) &&
		((_point.z >= _lowerBound.z) && (_point.z <= _upperBound.z)));
}

/* Finds the index in the m_triGrid that has this point in its area */
int Track::GetIndexAtPoint(Vector point)
{
	point -= m_smallest;
	point.x = floor(point.x / m_triSegSize);
	point.y = floor(point.y / m_triSegSize);
	point.z = floor(point.z / m_triSegSize);

	return static_cast<int>((point.z * m_triGridYX) + (point.y * m_triGridX) + point.x);
}

/* Similar to GetIndexAtPoint but instead returns the x,y and z indicies as if it were a 3D vector 
   (used in calculating where tri's go in the grid) */
void Track::GetXYZIndexAtPoint(Vector& _point)
{
	_point -= m_smallest;
	_point.x = floor(_point.x / m_triSegSize);
	_point.y = floor(_point.y / m_triSegSize);
	_point.z = floor(_point.z / m_triSegSize);
}