#pragma once
#include "TrackMagnet.h"
#include "KeybindManager.h"
#include "Banana.h"
#include "GreenShell.h"
#include "Mushroom.h"
#include "Constants.h"
#include "AnimationController.h"
#include "Bomb.h"
#include "FakeItemBox.h"
#include "ControlledMovement.h"
#include "MoveAI.h"
#include "Text2D.h"
#include "GoldenMushroom.h"
#include "Star.h"
#include "GiantMushroom.h"
#include "CharacterInfo.h"
#include "VehicleInfo.h"
#include "LightningCloud.h"
#include "RedShell.h"
#include <functional>

//=================================================================
//Base Player Class (i.e. a model GO3D the player controls)
//=================================================================

class Player : public TrackMagnet
{

public:
	Player(CharacterInfo _character, VehicleInfo _vehicle, int _playerID, std::function<Item*(ItemType)> _createItemFunction);
	~Player();

	virtual void Tick() override;
	virtual void Render() override;

	int GetWaypoint() { return m_waypoint; }
	int GetRanking() { return m_ranking; }
	int GetLap() { return m_lap; }
	bool GetFinished() { return m_finished; }
	Text2D* GetRankingText() { return m_textRanking; }
	Text2D* GetLapText() { return m_textLap; }
	Text2D* GetCountdown() { return m_textCountdown; }
	Text2D* GetFinishOrder() { return m_textFinishOrder; }
	ImageGO2D* GetItemImg() { return m_imgItem; }
	void SetItemPos(Vector2 _pos) { m_itemPos = _pos; }
	std::vector<std::string> GetOrderIndicator() { return m_orderIndicator; }

	void ExpensiveLoad() {
		m_animationMesh->Load();
	};

	void SetWaypoint(int _waypoint);
	void SetLap(int _lap) { m_lap = _lap; }
	void SetRanking(int _position) { m_ranking = _position; }
	void setGamePad(bool _state);
	void SetFinished(bool _finished) { m_finished = _finished; }

	/* Inventory Management */
	ItemType GetActiveItem() { return active_item; };
	void SetActiveItem(ItemType _item);
	ItemType GetItemInInventory() { return m_InventoryItem; };
	void SetItemInInventory(ItemType _item);
	LightningCloud* GetLightningCloud();

	void CheckUseItem();
	void TrailItems();
	void SpawnItems(ItemType type);
	void ReleaseItem();

	void Spin(int _revolutions, float _duration) { m_animationMesh->Spin(_revolutions, _duration); };
	void Flip(int _revolutions, float _duration) { m_animationMesh->Flip(_revolutions, _duration); };
	void Jump(float _jumpHeight, float _duration) { m_animationMesh->Jump(_jumpHeight, _duration); };

	bool isInvincible() { return m_invincible; };
	void setInvicible(bool _invincible) { m_invincible = _invincible; };

	void Reload(CharacterInfo _character, VehicleInfo _vehicle);

protected:
	int m_playerID = 0;

private:
	std::function<Item*(ItemType)> CreateItem;

	void movement();

	void RespawnLogic();
	void Respawn();
	void MovePlayerToTrack();

	void GlideLogic();

	ThICC_RenderData* m_RD = nullptr;
	KeybindManager m_keybind;
	Matrix m_savedMatrix;
	Vector m_savedPos;
	Vector m_savedVel;
	Vector m_savedGravVel;
	int m_ranking = 0;
	int m_waypoint = 0;
	int m_lap = 1;
	Text2D *m_textRanking = nullptr;
	Text2D *m_textLap = nullptr;
	Text2D *m_textCountdown = nullptr;
	Text2D *m_textFinishOrder = nullptr;
	Vector m_savedGravDir;
	bool m_finished = false;
	bool m_invincible = false;

	std::vector<std::string> m_orderIndicator{ "st","nd", "rd", "th" };

	// Player items:
	//	A player can have an ACTIVE item (e.g. holding a banana behind themselves) AND also an INVENTORY item.
	//	An inventory item is an item in the UI square which is held back ready to be used.
	//	If there is an item in inventory, the player cannot	aquire another.
	//	If there is an active item, the player can acquire one to their inventory.
	//	When an item is used it should move from inventory to active (or be immediately used, etc - some items differ).
	ItemType active_item = ItemType::NONE;
	ItemType m_InventoryItem = ItemType::NONE;
	
	Vector2 m_itemPos = Vector2(0, 0); // temp gpu fix 
	ImageGO2D *m_imgItem = nullptr;

	std::vector<Item*> m_trailingItems;
	std::vector<Item*> m_floatingItems; //Items which renders above the player - POW, Blooper, and Lightning Cloud
	void PositionFloatingItems();
	bool m_aPressed = true;
	bool m_multiItem = false;
	const int m_maxItems = 3;

	bool m_controlsActive = false;
	std::unique_ptr<ControlledMovement> m_move = nullptr;

	std::unique_ptr<AnimationController> m_animationMesh = nullptr;

	std::queue<Matrix> m_posHistory; // All the recorded player positions
	float m_posHistoryInterval = 0.2f; // How often the players position will be recorded
	int m_posHistoryLength = 4; // The length of the position queue
	float m_noTrackRespawn = 1; // If not on any terrain, respawn after this time
	float m_offTrackRespawn = 5; // If off the track, but still on terain, respawn after this time
	float m_stationaryRespawn = 5; // If not moving for this long, repawn
	float m_respawnSpeed = 30; // The speed at which lakitu moves the player back to the track

	// Respawn
	float m_posHistoryTimer = 0;
	float m_offTrackTimer = 0;
	float m_offTerrainTimer = 0;
	float m_timeSinceRespawn = 0;
	float m_timeStationary = 0;
	bool m_respawning = false;

	Matrix m_respawnStart = Matrix::Identity;
	Matrix m_respawnEnd = Matrix::Identity;
	Vector3 m_respawnPos = Vector3::Zero;
	float m_totalRespawnTime = 0;
	float m_elapsedRespawnTime = 0;

	bool m_preventRespawn = false; 

	// Gliding
	float m_minGlideDuration = 0.5f; // Gives the kart some time to leave the track so the glide doesn't immediatly end
	float m_glideTimeElapsed = 0;
	bool m_gliding = false;
	float m_normalGrav = 0; // Set from physmodel on load
	float m_glidingGrav = 5;

	std::unique_ptr<MoveAI> m_ai = nullptr;
};