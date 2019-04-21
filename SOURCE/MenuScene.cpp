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
	m_menu_state = menu_states::MAP_SELECT;
}

/* Create all 2D objects for the scene */
void MenuScene::create2DObjects()
{
	m_background = new ImageGO2D("MAIN_MENU_TEMP");

	//position map options
	int index = 0;
	for (MapInfo a_map : Locator::getGOS()->map_instances) {
		index++;

		//Text
		Text2D* map_name = new Text2D(a_map.name);
		if (index == 1) {
			map_name->SetText("> " + map_name->GetText());
		}
		map_name->SetColour(Colors::White);
		map_name->SetPos(Vector2(209, 55 + (index * 47)));
		m_mapTitles.push_back(map_name);

		//Image
		a_map.preview_sprite->SetPos(Vector2(812, 279));
		m_mapPreviews.push_back(a_map.preview_sprite);
	}

	//position character options
	index = 0;
	for (CharacterInfo a_character : Locator::getGOS()->character_instances) {
		index++;

		//Text
		Text2D* character_name = new Text2D(a_character.name);
		if (index == 1) {
			character_name->SetText("> " + character_name->GetText());
		}
		character_name->SetColour(Colors::White);
		character_name->SetPos(Vector2(209, 55 + (index * 47)));
		m_characterTitles.push_back(character_name);

		//Image
		a_character.preview_sprite->SetPos(Vector2(881, 285));
		a_character.preview_sprite->CentreOrigin();
		m_characterPreviews.push_back(a_character.preview_sprite);
	}

	//position vehicle options
	index = 0;
	for (VehicleInfo a_vehicle : Locator::getGOS()->vehicle_instances) {
		index++;

		//Text
		Text2D* vehicle_name = new Text2D(a_vehicle.name);
		if (index == 1) {
			vehicle_name->SetText("> " + vehicle_name->GetText());
		}
		vehicle_name->SetColour(Colors::White);
		vehicle_name->SetPos(Vector2(209, 55 + (index * 47)));
		m_vehicleTitles.push_back(vehicle_name);

		//Image
		a_vehicle.preview_sprite->SetPos(Vector2(881, 285));
		a_vehicle.preview_sprite->CentreOrigin();
		m_vehiclePreviews.push_back(a_vehicle.preview_sprite);
	}
}

/* Update the scene */
void MenuScene::Update(DX::StepTimer const& timer)
{
	switch (m_menu_state) {
		case menu_states::MAP_SELECT:
			//Exit
			if (m_keybinds.keyPressed("Quit"))
			{
				ExitGame();
			}

			//Change map selection
			if (m_keybinds.keyPressed("Down Arrow"))
			{
				if (highlighted_map < m_mapTitles.size() - 1) {
					m_mapTitles.at(highlighted_map)->SetText(m_mapTitles.at(highlighted_map)->GetText().substr(2));
					highlighted_map++;
					m_mapTitles.at(highlighted_map)->SetText("> " + m_mapTitles.at(highlighted_map)->GetText());
				}
			}
			if (m_keybinds.keyPressed("Up Arrow"))
			{
				if (highlighted_map > 0) {
					m_mapTitles.at(highlighted_map)->SetText(m_mapTitles.at(highlighted_map)->GetText().substr(2));
					highlighted_map--;
					m_mapTitles.at(highlighted_map)->SetText("> " + m_mapTitles.at(highlighted_map)->GetText());
				}
			}

			//Change to character select
			if (m_keybinds.keyPressed("Activate"))
			{
				m_menu_state = menu_states::CHARACTER_SELECT;
			}

			break;
		case menu_states::CHARACTER_SELECT:
			//Back to map select
			if (m_keybinds.keyPressed("Quit"))
			{
				m_menu_state = menu_states::MAP_SELECT;
			}

			//Change character selection
			if (m_keybinds.keyPressed("Down Arrow"))
			{
				if (highlighted_character < m_characterTitles.size() - 1) {
					m_characterTitles.at(highlighted_character)->SetText(m_characterTitles.at(highlighted_character)->GetText().substr(2));
					highlighted_character++;
					m_characterTitles.at(highlighted_character)->SetText("> " + m_characterTitles.at(highlighted_character)->GetText());
				}
			}
			if (m_keybinds.keyPressed("Up Arrow"))
			{
				if (highlighted_character > 0) {
					m_characterTitles.at(highlighted_character)->SetText(m_characterTitles.at(highlighted_character)->GetText().substr(2));
					highlighted_character--;
					m_characterTitles.at(highlighted_character)->SetText("> " + m_characterTitles.at(highlighted_character)->GetText());
				}
			}

			//Go to vehicle select
			if (m_keybinds.keyPressed("Activate"))
			{
				m_menu_state = menu_states::VEHICLE_SELECT;
			}

			break;
		case menu_states::VEHICLE_SELECT:
			//Back to character select
			if (m_keybinds.keyPressed("Quit"))
			{
				m_menu_state = menu_states::CHARACTER_SELECT;
			}

			//Change vehicle selection
			if (m_keybinds.keyPressed("Down Arrow"))
			{
				if (highlighted_vehicle < m_vehicleTitles.size() - 1) {
					m_vehicleTitles.at(highlighted_vehicle)->SetText(m_vehicleTitles.at(highlighted_vehicle)->GetText().substr(2));
					highlighted_vehicle++;
					m_vehicleTitles.at(highlighted_vehicle)->SetText("> " + m_vehicleTitles.at(highlighted_vehicle)->GetText());
				}
			}
			if (m_keybinds.keyPressed("Up Arrow"))
			{
				if (highlighted_vehicle > 0) {
					m_vehicleTitles.at(highlighted_vehicle)->SetText(m_vehicleTitles.at(highlighted_vehicle)->GetText().substr(2));
					highlighted_vehicle--;
					m_vehicleTitles.at(highlighted_vehicle)->SetText("> " + m_vehicleTitles.at(highlighted_vehicle)->GetText());
				}
			}

			//Load selected map with character choices
			if (m_keybinds.keyPressed("Activate"))
			{
				Locator::getGSD()->character_selected[0] = highlighted_character; //We only support P1 choices atm!
				Locator::getGSD()->vehicle_selected[0] = highlighted_vehicle;

				Locator::getAudio()->GetSound(SOUND_TYPE::MENU, (int)SOUNDS_MENU::MENU_LOOP)->Stop();
				m_scene_manager->setCurrentScene(Scenes::GAMESCENE + highlighted_map);
			}

			break;
	}
}

/* Render the 2D scene */
void MenuScene::Render2D(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>&  m_commandList)
{
	m_background->Render();
	switch (m_menu_state) {
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
