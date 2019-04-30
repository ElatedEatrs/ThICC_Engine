#include "pch.h"
#include "MenuScene.h"
#include "GameStateData.h"
#include "RenderData.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "Text2D.h"
#include "GameObjectShared.h"
#include <iostream>
#include <experimental/filesystem>

extern void ExitGame();

/* Create! */
MenuScene::MenuScene()
{
	//Get a ref to the scene manager for swapping scenes
	m_scene_manager = Locator::getSM();
}

/* Destroy! */
MenuScene::~MenuScene()
{
	m_mapTitles.clear();
	m_mapPreviews.clear();
	m_characterTitles.clear();
	m_characterPreviews.clear();
	delete m_background;
}

/* Load inexpensive things and create the objects for expensive things we will populate when required */
bool MenuScene::Load()
{
	create2DObjects();
	return true;
}

/* Reset on load */
void MenuScene::ExpensiveLoad() {
	m_menu_state = menu_states::SPLASH;
	m_timer = 0.0f;
	m_keybinds.Reset();
	highlighted_character = 0;
	highlighted_cup = 0;
	highlighted_map = 0;
	highlighted_vehicle = 0;
}

/* Create all 2D objects for the scene */
void MenuScene::create2DObjects()
{
	//Splashscreen objects
	m_splash_bg = new ImageGO2D("WHITE_720");
	m_logo = new ImageGO2D("engine_logo_white_720");
	m_logo->SetScale(Vector2(0.3, 0.3));
	m_logo->SetPos(Vector2(Locator::getRD()->m_window_width / 2.f, Locator::getRD()->m_window_height / 2.f));
	m_logo->CentreOrigin();

	//Main menu objects
	m_background = new ImageGO2D("MAIN_MENU_TEMP");
	m_state_desc = new Text2D("", Text2D::MIDDLE);
	m_state_desc->SetPos(Vector2(498, 620));
	m_state_desc->SetColour(Colors::Black);
	m_state_desc->SetScale(0.5f);

	//position cup options
	int index = 0;
	for (CupInfo* a_cup : Locator::getGOS()->cup_instances) {
		index++;

		//Text
		Text2D* cup_name = new Text2D(a_cup->name);
		cup_name->SetColour(inactive_colour);
		if (index == 1) {
			cup_name->SetColour(active_colour);
		}
		cup_name->SetPos(Vector2(209, 55 + (index * 47)));
		m_cupTitles.push_back(cup_name);

		//Image
		a_cup->preview_sprite->SetPos(Vector2(812, 279));
		m_cupPreviews.push_back(a_cup->preview_sprite);
	}
}

/* Update the scene */
void MenuScene::Update(DX::StepTimer const& timer)
{
	#ifdef _DEBUG
	//Hacky implementation to get to the debug scene (temp)
	if (Locator::getID()->m_keyboardTracker.IsKeyReleased(DirectX::Keyboard::Keys::D))
	{
		m_scene_manager->setCurrentScene(Scenes::DEBUG_LIGHTINGTEST);
	}
	#endif

	switch (m_menu_state) {
		case menu_states::SPLASH:
			//Animate logo over time
			m_logo->SetScale(Vector2(0.3 + (m_timer / 30), 0.3 + (m_timer / 30)));
			m_timer += (float)timer.GetElapsedSeconds();
			if (m_timer > m_timeout) {
				m_menu_state = menu_states::CUP_SELECT;
			}

			//Allow skip
			if (m_keybinds.keyReleased("Activate"))
			{
				m_menu_state = menu_states::CUP_SELECT;
			}

			break;
		case menu_states::CUP_SELECT:
			m_state_desc->SetText(m_localiser.getString("cup_select"));

			//Exit
			if (m_keybinds.keyReleased("Quit")) {
				ExitGame();
			}

			//Change cup selection
			if (m_keybinds.keyReleased("Menu Down") || m_keybinds.keyReleased("backwards"))
			{
				if (highlighted_cup < m_cupTitles.size() - 1) {
					m_cupTitles.at(highlighted_cup)->SetColour(inactive_colour);
					highlighted_cup++;
					m_cupTitles.at(highlighted_cup)->SetColour(active_colour);
				}
			}
			if (m_keybinds.keyReleased("Menu Up") || m_keybinds.keyReleased("forward"))
			{
				if (highlighted_cup > 0) {
					m_cupTitles.at(highlighted_cup)->SetColour(inactive_colour);
					highlighted_cup--;
					m_cupTitles.at(highlighted_cup)->SetColour(active_colour);
				}
			}

			//Change to map select
			if (m_keybinds.keyReleased("Activate")) {
				m_mapTitles.clear();
				m_mapPreviews.clear();

				//position map options
				int index = 0;
				for (MapInfo* a_map : Locator::getGOS()->map_instances) {
					//Only include maps from this cup
					if (a_map->cup->codename != Locator::getGOS()->cup_instances.at(highlighted_cup)->codename) {
						continue;
					}

					#ifndef _DEBUG
					//Show/hide map options based on arcade exclusivity
					#ifdef _ARCADE
					if (!a_map->is_arcade_exclusive) {
						return;
					}
					#else
					if (a_map->is_arcade_exclusive) {
						return;
					}
					#endif
					#endif

					index++;

					//Text
					Text2D* map_name = new Text2D(a_map->name);
					map_name->SetColour(inactive_colour);
					if (index == 1) {
						map_name->SetColour(active_colour);
					}
					map_name->SetPos(Vector2(209, 55 + (index * 47)));
					m_mapTitles.push_back(map_name);

					//Image
					a_map->preview_sprite->SetPos(Vector2(812, 279));
					m_mapPreviews.push_back(a_map->preview_sprite);
				}

				//Swap scene
				m_menu_state = menu_states::MAP_SELECT;
			}
			break;
		case menu_states::MAP_SELECT:
			m_state_desc->SetText(m_localiser.getString("map_select"));

			//Back to cup select
			if (m_keybinds.keyReleased("Back"))
			{
				m_menu_state = menu_states::CUP_SELECT;
			}

			//Change map selection
			if (m_keybinds.keyReleased("Menu Down") || m_keybinds.keyReleased("backwards"))
			{
				if (highlighted_map < m_mapTitles.size() - 1) {
					m_mapTitles.at(highlighted_map)->SetColour(inactive_colour);
					highlighted_map++;
					m_mapTitles.at(highlighted_map)->SetColour(active_colour);
				}
			}
			if (m_keybinds.keyReleased("Menu Up") || m_keybinds.keyReleased("forward"))
			{
				if (highlighted_map > 0) {
					m_mapTitles.at(highlighted_map)->SetColour(inactive_colour);
					highlighted_map--;
					m_mapTitles.at(highlighted_map)->SetColour(active_colour);
				}
			}

			//Change to character select
			if (m_keybinds.keyReleased("Activate"))
			{
				m_characterTitles.clear();
				m_characterPreviews.clear();

				//position character options
				int index = 0;
				for (CharacterInfo* a_character : Locator::getGOS()->character_instances) {
					index++;

					//Text
					Text2D* character_name = new Text2D(a_character->name);
					character_name->SetColour(inactive_colour);
					if (index == 1) {
						character_name->SetColour(active_colour);
					}
					character_name->SetPos(Vector2(209, 55 + (index * 47)));
					m_characterTitles.push_back(character_name);

					//Image
					a_character->preview_sprite->SetPos(Vector2(881, 285));
					m_characterPreviews.push_back(a_character->preview_sprite);
				}

				//swap scene
				m_menu_state = menu_states::CHARACTER_SELECT;
			}

			break;
		case menu_states::CHARACTER_SELECT:
			m_state_desc->SetText(m_localiser.getString("character_select"));

			//Back to map select
			if (m_keybinds.keyReleased("Back"))
			{
				m_menu_state = menu_states::MAP_SELECT;
			}

			//Change character selection
			if (m_keybinds.keyReleased("Menu Down") || m_keybinds.keyReleased("backwards"))
			{
				if (highlighted_character < m_characterTitles.size() - 1) {
					m_characterTitles.at(highlighted_character)->SetColour(inactive_colour);
					highlighted_character++;
					m_characterTitles.at(highlighted_character)->SetColour(active_colour);
				}
			}
			if (m_keybinds.keyReleased("Menu Up") || m_keybinds.keyReleased("forward"))
			{
				if (highlighted_character > 0) {
					m_characterTitles.at(highlighted_character)->SetColour(inactive_colour);
					highlighted_character--;
					m_characterTitles.at(highlighted_character)->SetColour(active_colour);
				}
			}

			//Go to vehicle select
			if (m_keybinds.keyReleased("Activate"))
			{
				m_vehicleTitles.clear();
				m_vehiclePreviews.clear();

				//position vehicle options
				int index = 0;
				for (VehicleInfo* a_vehicle : Locator::getGOS()->vehicle_instances) {
					index++;

					//Text
					Text2D* vehicle_name = new Text2D(a_vehicle->name);
					vehicle_name->SetColour(inactive_colour);
					if (index == 1) {
						vehicle_name->SetColour(active_colour);
					}
					vehicle_name->SetPos(Vector2(209, 55 + (index * 47)));
					m_vehicleTitles.push_back(vehicle_name);

					//Image
					a_vehicle->preview_sprite->SetPos(Vector2(881, 285));
					m_vehiclePreviews.push_back(a_vehicle->preview_sprite);
				}
				
				//swap scene
				m_menu_state = menu_states::VEHICLE_SELECT;
			}

			break;
		case menu_states::VEHICLE_SELECT:
			m_state_desc->SetText(m_localiser.getString("vehicle_select"));

			//Back to character select
			if (m_keybinds.keyReleased("Back"))
			{
				m_menu_state = menu_states::CHARACTER_SELECT;
			}

			//Change vehicle selection
			if (m_keybinds.keyReleased("Menu Down") || m_keybinds.keyReleased("backwards"))
			{
				if (highlighted_vehicle < m_vehicleTitles.size() - 1) {
					m_vehicleTitles.at(highlighted_vehicle)->SetColour(inactive_colour);
					highlighted_vehicle++;
					m_vehicleTitles.at(highlighted_vehicle)->SetColour(active_colour);
				}
			}
			if (m_keybinds.keyReleased("Menu Up") || m_keybinds.keyReleased("forward"))
			{
				if (highlighted_vehicle > 0) {
					m_vehicleTitles.at(highlighted_vehicle)->SetColour(inactive_colour);
					highlighted_vehicle--;
					m_vehicleTitles.at(highlighted_vehicle)->SetColour(active_colour);
				}
			}

			//Load selected map with character choices
			if (m_keybinds.keyReleased("Activate"))
			{
				Locator::getGSD()->character_selected[0] = highlighted_character; //We only support P1 choices atm!
				Locator::getGSD()->vehicle_selected[0] = highlighted_vehicle;

				Locator::getAudio()->GetSound(SoundType::MENU, (int)MenuSounds::MENU_LOOP)->Stop();
				m_scene_manager->setCurrentScene(Scenes::GAMESCENE + highlighted_map);
			}

			break;
	}
}

/* Render the 2D scene */
void MenuScene::Render2D(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>&  m_commandList)
{
	if (m_menu_state == menu_states::SPLASH) {
		m_splash_bg->Render();
		m_logo->Render();
		return;
	}

	m_background->Render();
	m_state_desc->Render();
	switch (m_menu_state) {
		case menu_states::CUP_SELECT:
			m_cupPreviews.at(highlighted_cup)->Render();
			for (std::vector<Text2D*>::iterator it = m_cupTitles.begin(); it != m_cupTitles.end(); it++) {
				(*it)->Render();
			}
			break;
		case menu_states::MAP_SELECT:
			m_mapPreviews.at(highlighted_map)->Render();
			for (std::vector<Text2D*>::iterator it = m_mapTitles.begin(); it != m_mapTitles.end(); it++) {
				(*it)->Render();
			}
			break;
		case menu_states::CHARACTER_SELECT:
			m_characterPreviews.at(highlighted_character)->Render();
			for (std::vector<Text2D*>::iterator it = m_characterTitles.begin(); it != m_characterTitles.end(); it++) {
				(*it)->Render();
			}
			break;
		case menu_states::VEHICLE_SELECT:
			m_vehiclePreviews.at(highlighted_vehicle)->Render();
			for (std::vector<Text2D*>::iterator it = m_vehicleTitles.begin(); it != m_vehicleTitles.end(); it++) {
				(*it)->Render();
			}
			break;
	}
}
