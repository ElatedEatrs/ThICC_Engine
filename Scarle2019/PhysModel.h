#pragma once
#include "SDKMeshGO3D.h"
#include "Collision.h"
#include <json.hpp>
using json = nlohmann::json;

struct PhysModelData {
	float scale = 1.0f;
};

class PhysModel : public SDKMeshGO3D
{
public:

	PhysModel(RenderData* _RD, string _filename);
	virtual ~PhysModel() = default;

	void initCollider(json &model_data);
	bool hasCollider() {return m_hasCollider;};
	void updateCollider();

	virtual void Tick(GameStateData* _GSD) override;

	bool		IsPhysicsOn() { return m_physicsOn; }
	float		GetDrag() { return m_drag; }

	void		SetPhysicsOn(bool _physics) { m_physicsOn = _physics; }
	void		TogglePhysics() { m_physicsOn = !m_physicsOn; }
	void		SetDrag(float _drag) { m_drag = _drag; }

	BoundingOrientedBox getCollider() { return m_collider; };
	void addCurrentCollision(Collision _currentCollision) { m_currentCollisions.push_back(_currentCollision); };

	SDKMeshGO3D* getDebugCollider() { return m_colliderDebug; };

protected:

	//very basic physics
	bool m_physicsOn = false;
	float m_drag = 0.0f;
	Vector3 m_velTotal = Vector3::Zero; // The total velocity to apply each frame
	Vector3 m_vel = Vector3::Zero; // The amount of player added velocity to apply each frame

	Vector3 m_gravDirection = Vector3::Down;
	Vector3 m_gravVel = Vector3::Zero; // The amount of gravity velocity to apply each frame
	float m_maxGrav = 60; // The maximum length of m_gravVel. m_gravVel will be clamped to this
	Vector3 m_acc = Vector3::Zero;
	PhysModelData m_physData;

	std::vector<Collision> m_currentCollisions;

	bool m_hasCollider = false;
	BoundingOrientedBox m_collider; //Bounding box of the model

	SDKMeshGO3D* m_colliderDebug = nullptr;
	XMFLOAT3 m_collLocalCentre;//Local Centre of the mesh
	XMFLOAT3 m_collWorldCentre;//World Centre of the mesh and the centre of the bounding box
	//Corner Pos in Local Space
	Vector3 m_frontTopLeft;
	Vector3 m_frontTopRight;
	Vector3 m_backBottomLeft;
	Vector3 m_backBottomRight;
	//Corner Pos in World Space
	Vector3 m_globalFrontLeft;
	Vector3 m_globalFrontRight;
	Vector3 m_globalBackLeft;
	Vector3 m_globalBackRight;
	float m_width;
	float m_length;
	float m_height;

	XMFLOAT3 MatrixDecomposeYawPitchRoll(Matrix  mat);

};