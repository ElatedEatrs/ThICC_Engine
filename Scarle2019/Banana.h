#pragma once

#include "Item.h"

class Banana : public Item {
public:
	Banana();
	~Banana() = default;

	virtual void Tick() override { Item::Tick(); };

	void Use(Player* player) override {};
	void HitByPlayer(Player* player) override;
};