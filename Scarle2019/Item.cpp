#include "pch.h"
#include "Item.h"
#include <fstream>

Item::Item(const std::string& item_type) 
{
	//Set model name
	m_mesh = new TrackMagnet(item_type);
	m_mesh->SetShouldRender(false);
	m_displayedMesh = std::make_unique<AnimationMesh>(item_type);
}

void Item::Tick()
{
	if (m_mesh)
	{
		m_mesh->Tick();
		m_displayedMesh->Update(m_mesh->GetWorld(), m_mesh->GetWorld().Forward());
	}

	if (m_itemUsed)
	{
		//Despawn time
		m_elapsedTime += Locator::getGSD()->m_dt;
		if (m_elapsedTime > m_maxDuration)
		{
			m_shouldDestroy = true;
		}

		//Player immunity time
		if (m_player)
		{
			std::cout << std::to_string(m_elapsedImmunityTime) << std::endl;
			m_elapsedImmunityTime += Locator::getGSD()->m_dt;
			if (m_elapsedImmunityTime >= m_maxImmunityTime)
			{
				m_player = nullptr;
			}
		}
	}
}

bool Item::ignorePlayerCollisions(Player* player)
{
	return (m_player && player == m_player) || m_trailingPlayerImmunity;	
}

void Item::setItemInUse(Player* player)
{
	m_itemUsed = true;
	m_trailingPlayerImmunity = false;
	m_player = player;
}
