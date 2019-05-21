#pragma once
#include "Collision.h"
#include "Player.h"
#include "Item.h"
#include <vector>
#include <json.hpp>
using json = nlohmann::json;

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	static void InitConfig();
	static std::vector<Collision> CollisionDetection(std::vector<PhysModel*> _physModel, std::vector<Item*> _items);
	static PlayerCollisionTypes CollisionResponse(Collision* this_collision);

private:
	static std::vector<Collision> CheckPhysModelCollisions(std::vector<PhysModel*> _physModels);
	static void CheckResolveItemCollisions(std::vector<PhysModel*> _physModels, std::vector<Item*> _items);
	static bool bombResponse(Item * item1, Item * item2);
	static void fakeBoxResponse(Item * item1, Item * item2);

	static bool CheckItemImmunity(Item* _item1, Item* _item2);

	static void PlayerCollisions(PhysModel*& _player1, PhysModel*& _player2, Vector3 _collisionNormal);
	static void ApplyInvincibleResponse(Player * player2);
	static void LightningCloudCollision(Player * player2, Player * player1);
	static void ItemBoxCollision(PhysModel*& _player, PhysModel*& _itemBox);
	static void ExplosionCollision(PhysModel*& _player, PhysModel*& _explosion);

	static Plane getPlane(Vector3 _corner1, Vector3 _corner2, float height);

	static float m_thresholdDistSqrd;
	static ItemCollisionData m_collisionData;
};

