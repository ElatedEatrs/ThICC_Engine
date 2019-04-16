#pragma once

#include "pch.h"
#include "Player.h"
#include "Item.h"

class Mushroom : public Item {
public:
	Mushroom();
	~Mushroom() = default;

	virtual void Tick() override;
	void HitByPlayer(Player* player) override;
	void Use(Player* player, bool _altUse) override;

private:
	Player * m_player = nullptr;
	bool m_used = false;


	double m_timeElapsed = 0;

	float m_boostAmount = 40;
	float m_minVelo = 50;
	double m_boostDuration = 2;
};