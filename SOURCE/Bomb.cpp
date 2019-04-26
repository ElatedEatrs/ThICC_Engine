#include "pch.h"
#include "Bomb.h"
#include "Player.h"
#include "Explosion.h"
#include "GameStateData.h"
#include <iostream>

Bomb::Bomb(std::function<Explosion*(ItemType)> _CreateExplosionFunciton) : Item(Locator::getItemData()->GetItemModelName(BOMB)), CreateExplosion(_CreateExplosionFunciton)
{
	m_mesh->SetDrag(0.9f);
	m_mesh->SetPhysicsOn(true);
	m_maxImmunityTime = 0.1;

	initItemData();
}

void Bomb::initItemData()
{
	m_countdownTime = (float)m_itemData["BOMB"]["info"]["detonation_time"];

	m_throwData.m_thowHoriPosOffset = m_itemData["BOMB"]["info"]["throw"]["horizontal_pos_offset"];
	m_throwData.m_thowVertPosOffset = m_itemData["BOMB"]["info"]["throw"]["vertical_pos_offset"];
	m_throwData.m_forwardForce = m_itemData["BOMB"]["info"]["throw"]["forward_force"];
	m_throwData.m_upwardForce = m_itemData["BOMB"]["info"]["throw"]["upward_force"];
	m_throwData.m_maxGrav = m_itemData["BOMB"]["info"]["throw"]["max_gravity"];
}

void Bomb::Tick()
{
	Item::Tick();

	if (m_countdown)
	{
		m_current_time += Locator::getGSD()->m_dt;

		if (m_current_time >= m_countdownTime)
		{
			Detonate();
		}
	}
}

void Bomb::Use(Player * player, bool _altUse)
{
	Item::setItemInUse(player);

	if (_altUse)
	{
		//Positions the bomb
		m_mesh->SetWorld(player->GetWorld());
		m_mesh->AddPos(player->GetWorld().Right() * m_throwData.m_thowHoriPosOffset + player->GetWorld().Up() * m_throwData.m_thowVertPosOffset);
		m_mesh->UpdateWorld();

		//Yeets said bomb
		m_mesh->setMaxGrav(m_throwData.m_maxGrav);
		m_mesh->setGravVelocity(player->getVelocity() + (player->GetWorld().Forward() * m_throwData.m_forwardForce) + (player->GetWorld().Up() * m_throwData.m_upwardForce));
	}
	m_countdown = true;
	//Detonate();
}

void Bomb::Detonate()
{
	m_countdown = false;
	explosion = CreateExplosion(BOMB);
	explosion->SetWorld(m_mesh->GetWorld());
	explosion->explode();
	FlagForDestoy();
}

void Bomb::HitByPlayer(Player * player)
{
	if (Item::ignorePlayerCollisions(player))
	{
		return;
	}
	Detonate();
}
