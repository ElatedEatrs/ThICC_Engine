#include "pch.h"
#include "ItemBox.h"
#include "ServiceLocator.h"
#include "Player.h"
#include "ItemProbability.h"
#include "Constants.h"

//Todo: replace "Default Item" with item box model
ItemBox::ItemBox(Vector3& position, Vector3& rotation) : PhysModel("Default Item") {
	SetPos(position);
	SetRotation(rotation);

	std::cout << "CREATING ITEM BOX AT: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
}

void ItemBox::hasCollided(Player* collided_player) {
	setVisible(false);
	collided_player->setItemInInventory(Locator::getProbabilities()->GetRandomItem(collided_player->GetRanking()));
}

void ItemBox::Tick() {
	if (!isVisible()) {
		invisibility_timer += Locator::getGSD()->m_dt;
		if (invisibility_timer >= ItemBoxConfig::respawn_time) {
			setVisible(true);
			invisibility_timer = 0.0;
		}
	}

	PhysModel::Tick();
}