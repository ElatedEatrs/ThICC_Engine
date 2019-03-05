#pragma once
#include "GameObject3D.h"
struct GameStateData;

//This is a basic camera class
//if the pointer to a GameObject3D != NULL this will be targeted at that object
//else it will look at the point m_targetPos

class Camera :
	public GameObject3D
{
public:
	enum class BEHAVIOUR : int
	{
		BEHIND= 0,
		FRONT = 1,
		LERP = 2,
		ORBIT = 3,
		CINEMATIC = 4,
	};

	Camera(float _width, float _height, float _near, float _far, GameObject3D* _target, Vector3 _dpos);
	virtual ~Camera();

	void SetTarget(GameObject3D* _target) { m_targetObject = _target; }
	void SetTarget(Vector3 _target) { m_targetObject = NULL; m_targetPos = _target; }
	void SetDPos(Vector3 _m_dpos) {  m_dpos = _m_dpos; }
	void SetBehav(BEHAVIOUR _behav) { behav = _behav; }

	Matrix GetProj() { return m_proj; }
	Matrix GetView() { return m_view; }
	Vector3 GetDeltaPos() { return m_dpos; };

	virtual void Tick(GameStateData* _GSD);
	virtual void Render(RenderData* _RD) {};



protected:

	GameObject3D* m_targetObject = NULL;
	Vector3 m_targetPos = Vector3::Zero;
	Matrix m_proj = Matrix::Identity;
	Matrix m_view = Matrix::Identity;
	Vector3	m_dpos; //I'll lurk this far behind and away from it
	std::vector<Vector3> points;
	std::vector<Vector3> rotations;
	BEHAVIOUR behav = BEHAVIOUR::LERP;

	float angle = 0.0f;
	int at = 1;
	float time_out = 5.0f;
	float timer = 0.0f;
};

