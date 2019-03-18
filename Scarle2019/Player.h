#pragma once
#include "TrackMagnet.h"
#include "KeybindManager.h"
#include "Banana.h"
#include "GreenShell.h"
#include "Constants.h"
#include <functional>

//=================================================================
//Base Player Class (i.e. a model GO3D the player controls)
//=================================================================

class Player : public TrackMagnet
{

public:
	Player(string _filename, int _playerID, std::function<Item*(ItemType)> _createItemFunction);
	~Player();

	virtual void Tick() override;
	int GetWaypoint() { return waypoint; }
	int GetRanking() { return ranking; }
	int GetLap() { return lap; }
	Text2D* GetRankingText() { return text_ranking; }
	Text2D* GetLapText() { return text_lap; }

	void SetWaypoint(int _waypoint) { waypoint = _waypoint; }
	void SetLap(int _lap) { lap = _lap; }
	void SetRanking(int _position) { ranking = _position; }

	void setCurrentWaypoint(int waypoint) { current_waypoint = waypoint; }
	void setGamePad(bool _state);

	/* Inventory Management */
	ItemType getActiveItem() { return active_item; };
	void setActiveItem(ItemType _item) { 
		if (inventory_item == _item) { 
			active_item = _item; 
			inventory_item = ItemType::NONE;
		} 
		else
		{
			//We should never get here - so if we do, throw a useful error.
			throw std::runtime_error("Player tried to use an item that they did not have. This should never be requested!");
		}
	};
	ItemType getItemInInventory() { return inventory_item; };
	void setItemInInventory(ItemType _item) {
		if (inventory_item == ItemType::NONE) {
			inventory_item = _item;
		}
	}
	
protected:
	int m_playerID = 0;

private:
	std::function<Item*(ItemType)> CreateItem;
	void movement();

	RenderData* m_RD;
	KeybindManager m_keymindManager;
	Matrix m_savedMatrix;
	Vector m_savedPos;
	Vector m_savedVel;
	Vector m_savedGravVel;
	int ranking = 0;
	int waypoint = 0;
	int lap = 1;
	Text2D *text_ranking = nullptr;
	Text2D *text_lap = nullptr;
	Vector m_savedGravDir;

	// Player items:
	//	A player can have an ACTIVE item (e.g. holding a banana behind themselves) AND also an INVENTORY item.
	//	An inventory item is an item in the UI square which is held back ready to be used.
	//	If there is an item in inventory, the player cannot	aquire another.
	//	If there is an active item, the player can acquire one to their inventory.
	//	When an item is used it should move from inventory to active (or be immediately used, etc - some items differ).
	ItemType active_item = ItemType::NONE;
	ItemType inventory_item = ItemType::NONE;
	
	int current_position = 0;
	int current_waypoint = 0;
	int next_waypoint = 0;
	Text2D *position = nullptr;
	bool m_controlsActive = false;
};