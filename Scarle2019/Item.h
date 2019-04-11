#pragma once

#include "GameFilepaths.h"
#include "TrackMagnet.h"
#include "ServiceLocator.h"
#include "ItemData.h"
#include "Deletable.h"
#include "AnimationMesh.h"

class Player;

class Item  : public Deletable
{
public:
	Item() = default;
	Item(const std::string& item_type);
	~Item() = default;
	
	virtual void Tick();
	virtual void HitByPlayer(Player* _player) = 0;
	virtual void Use(Player* _player, bool _altUse) = 0;

	bool ShouldDestroy() { return m_shouldDestroy; };
	void FlagForDestoy() { m_shouldDestroy = true; };

	TrackMagnet* GetMesh() { return m_mesh; };
	SDKMeshGO3D* GetRenderMesh() { return m_displayedMesh.get(); };

	virtual void AddImmuneItem(Item* _item) { m_immuneItems.push_back(_item); };
	virtual void addImmuneItems(std::vector<Item*> _immuneItems) { m_immuneItems = _immuneItems; };
	virtual std::vector<Item*> GetImmuneItems() { return m_immuneItems; };
	virtual void setTrailingPlayerImmunity(bool _immunity) { m_trailingPlayerImmunity = _immunity; };

	virtual Player* getPlayer() { return m_player; };
	virtual void setPlayer(Player* _player) { m_player = _player; };

	virtual float getSpinAngle() { return m_spinAngle; };
	virtual void setSpinAngle(float _angle) { m_spinAngle = _angle; };

protected:
	TrackMagnet * m_mesh = nullptr;
	Player* m_player = nullptr;

	std::unique_ptr<AnimationMesh> m_displayedMesh = nullptr;
	bool m_shouldDestroy = false;
	bool m_itemUsed = false;
	bool m_trailingPlayerImmunity = true;

	//Despawn Time
	float m_elapsedTime = 0;
	float m_maxDuration = 300;

	//Player Immunity time
	float m_elapsedImmunityTime = 0;
	float m_maxImmunityTime = 0;

	//Angle of orbit around player
	float m_spinAngle = 0;

	//Vector of items that are immune to this items collisions - needed for triple banana
	std::vector<Item*> m_immuneItems;

	virtual bool ignorePlayerCollisions(Player* player);
	virtual void setItemInUse(Player* player);
};