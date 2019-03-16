#pragma once

#include "StepTimer.h"
#include "Scene.h"
#include "LocalisationManager.h"
#include "Banana.h" //test
#include "CollisionManager.h"
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

	void Update() override;
	void Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList1>&  m_commandList) override;
	bool Load() override;

private:
	//State Stuff
	bool m_isPaused;

	void create2DObjects();
	void create3DObjects();
	void pushBackObjects();

	// Test objects
	Track* track = nullptr;
	Player* player[4] = { nullptr };
	PhysModel* test_model = nullptr;

	vector<GameObject2D*>								m_2DObjects; //data structure for all 2D Objects
	vector<GameObject3D*>								m_3DObjects; //data structure for all 3D Objects
	//std::ptr<DirectX::SpriteBatch> m_spriteBatch[4]{NULL};
	Camera*												m_cam[4];
	Light*												m_light;

	KeybindManager m_keybinds;
	//Banana m_banana_test;

	std::vector<PhysModel*> m_physModels;

	json game_config;
	LocalisationManager m_localiser;
	GameFilepaths m_filepath;
	SceneManager* m_scene_manager;
};

