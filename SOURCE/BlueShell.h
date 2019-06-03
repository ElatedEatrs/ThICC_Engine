#pragma once
#include "Item.h"
#include "MoveAI.h"
#include "ControlledMovement.h"
#include "ItemAiData.h"
#include "Explosion.h"

class BlueShell : public Item
{
public:
	BlueShell(std::function<Explosion*(ItemType)> _CreateExplosionFunciton, std::vector<Player*> _players);
	~BlueShell() = default;

	virtual void Tick() override;
	virtual void HitByPlayer(Player* _player) override;
	virtual void Use(Player* _player, bool _altUse) override;
private:
	void FindTargetPlayer();

	std::unique_ptr<MoveAI> m_ai = nullptr;
	std::unique_ptr<ControlledMovement> m_move = nullptr;
	ItemAiData m_aiData;

	std::function<Explosion*(ItemType)> CreateExplosion;
	Explosion* m_explosion;

	std::vector<Player*> m_players;
	Player* m_targetPlayer = nullptr;

	enum MoveState {UP, ACROSS, DOWN} m_moveState = UP;
	
};

