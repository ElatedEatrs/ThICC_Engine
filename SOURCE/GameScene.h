#pragma once

#include "StepTimer.h"
#include "Scene.h"
#include "LocalisationManager.h"
#include "Banana.h" //test
#include "Mushroom.h"
#include "GreenShell.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "AIScheduler.h"
#include <vector>

using std::vector;

//predefs
class GameObject2D;
class GameObject3D;
struct RenderData;
struct InputData;
class SceneManager;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	//Core update/render/load functions
	void Update() override;
	void Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>&  m_commandList) override;
	bool Load() override;

private:
	//Handle player's waypoints and placements
	void SetPlayersWaypoint();
	void SetPlayerRanking();

	// Updates
	void UpdateItems();
	void DeleteItem(Item * item);
	void DeleteThread(Item * item);

	//State Stuff
	bool m_isPaused;

	//Item creation
	void create2DObjects() override;
	void create3DObjects() override;
	void pushBackObjects() override;

	//Structures for the scene's objects
	vector<GameObject2D*> m_2DObjects;
	vector<GameObject3D*> m_3DObjects;
	std::vector<PhysModel*> m_physModels;

	//Common engine components
	LocalisationManager m_localiser;
	KeybindManager m_keybinds;
	GameFilepaths m_filepath;

	//Item objects
	Item* CreateItem(ItemType type);
	Explosion* CreateExplosion();

	//Game objects (and test crap)
	Track* track = nullptr;
	Player* player[4] = { nullptr };
	PhysModel* test_model = nullptr;
	SDKMeshGO3D* debug_cups[8] = { nullptr };
	std::vector<Item*> m_itemModels;
	Text2D* countdown_text = nullptr;

	//Cameras
	Camera* m_cam[4];
	Camera*	cine_cam;

	//Referenced stuff
	json game_config;
	json track_config;
	RenderData* m_RD;

	//lol wtf
	SceneManager* m_scene_manager;

	//Timing
	float timeout = 12.f;

	//Game states
	enum States {
		START = 0,
		OPENING = 1,
		CAM_OPEN = 2,
		COUNTDOWN = 3,
		PLAY = 4,
		END = 5
	};
	States state = START;
	bool m_playerControls = false;
	bool track_music_start = true;
	bool final_lap_start = false;
	bool final_lap = false;
	int finished = 0;

	//AI
	std::unique_ptr<AIScheduler> m_aiScheduler = nullptr;

};

