#include "pch.h"
#include "Game.h"
#include "RenderData.h"
#include "AudioManager.h"

#include "MenuScene.h"
#include "GameScene.h"
#include "DebugScene.h"
#include "LoadingScene.h"

/* Perform initialisation */
void ThICC_Game::Initialize() {
	//Read in game config - this could really do with being passed out to everything rather than being loaded over and over!
	std::ifstream i(m_filepath.generateFilepath("GAME_CORE", m_filepath.CONFIG));
	game_config << i;

	//Share out object data
	Locator::setupGOS(&m_go_shared);

	//Send out scene manager instance for scenes to grab
	Locator::setupSM(&m_scene_manager);
	m_scene_manager.Initialize();

	//Set up AI scheduler
	m_aiScheduler = std::make_unique<AIScheduler>();
	Locator::setupAIScheduler(m_aiScheduler.get());

	//Load all common model names
	std::ifstream x(m_filepath.generateConfigFilepath("COMMON_MODELS_CONFIG", m_filepath.CONFIG));
	m_go_shared.common_model_config << x;

	#ifdef _ARCADE
	//Load arcade cubemap
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string cubemap_radiance_str = m_filepath.generateFilepath("WHITE_CUBEMAP", m_filepath.CUBEMAP_RADIANCE);
	Locator::getRD()->arcade_cubemap = converter.from_bytes(cubemap_radiance_str.c_str());
	#endif

	//Load all character data
	std::ifstream p(m_filepath.generateFilepath("CHARACTER_CONFIG", m_filepath.CONFIG));
	character_config << p;
	int index = 0;
	for (auto& element : character_config) {
		CharacterInfo* new_chr_inf = new CharacterInfo(element);
		m_go_shared.character_instances.push_back(new_chr_inf);
		Locator::getAudio()->addToSoundsList(m_go_shared.character_instances[index]->audio, m_go_shared.character_instances[index]->name);
		index++;
	}

	//Load all cups (must be done before maps)
	std::ifstream g(m_filepath.generateFilepath("CUP_CONFIG", m_filepath.CONFIG));
	cup_config << g;
	for (auto it : cup_config.items()) {
		CupInfo* new_cup_inf = new CupInfo(it.key(), it.value());
		m_go_shared.cup_instances.push_back(new_cup_inf);
	}

	//Load all vehicle data
	std::ifstream k(m_filepath.generateFilepath("VEHICLE_CONFIG", m_filepath.CONFIG));
	vehicle_config << k;
	for (auto& element : vehicle_config) {
		VehicleInfo* new_veh_inf = new VehicleInfo(element);
		m_go_shared.vehicle_instances.push_back(new_veh_inf);
	}

	//Create all game scenes (all maps) and store map preview data
	std::ifstream j(m_filepath.generateFilepath("MAP_CONFIG", m_filepath.CONFIG));
	map_config << j;
	index = 0;
	MapInfo* attract_state = nullptr;
	for (auto& element : map_config) {
		//Store map info
		MapInfo* new_map_inf = new MapInfo(element, index);
		#ifdef _ARCADE
		if (!new_map_inf->is_arcade_exclusive) {
			continue;
		}
		attract_state = new_map_inf; //FFS
		#else
		if (new_map_inf->is_arcade_exclusive) {
			attract_state = new_map_inf;
			#ifndef _DEBUG
			continue;
			#endif
		}
		#endif
		m_go_shared.map_instances.push_back(new_map_inf);
		//Create scene
		m_scene_manager.addScene(new GameScene(m_go_shared.map_instances.at(index)), (int)Scenes::GAMESCENE + index);
		index++;
	}

	//Create the scenes
	m_scene_manager.addScene(new MenuScene(), (int)Scenes::MENUSCENE);
	m_scene_manager.addScene(new LoadingScene(), (int)Scenes::LOADINGSCENE);
	m_scene_manager.addScene(new GameScene(attract_state), (int)Scenes::ATTRACT_STATE);
	#ifdef _DEBUG 
	m_scene_manager.addScene(new DebugScene(), (int)Scenes::DEBUG_LIGHTINGTEST);
	#endif

	//Set our default scene
	m_scene_manager.setCurrentScene(Scenes::MENUSCENE, true);
}

/* Update loop */
void ThICC_Game::Update(DX::StepTimer const& timer) {
	m_scene_manager.Update(timer);
}

/* Render loop 3D */
void ThICC_Game::Render3D() {
	m_scene_manager.Render3D(Locator::getRD()->m_commandList);
}

/* Render loop 2D */
void ThICC_Game::Render2D() {
	m_scene_manager.Render2D(Locator::getRD()->m_commandList);
}