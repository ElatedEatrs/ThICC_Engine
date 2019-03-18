#pragma once
#include <vector>

/*

	!!!		DO NOT REORDER ANY OF THESE ENUMS!		!!!

*/

enum Scenes
{
	MENUSCENE,
	GAMESCENE,
	DEBUGSCENE,

	SCENE_COUNT // must always be last!
};

enum States
{
	NOSTATE = -1,
	PAUSED = 0,

	//MENU
	LOBBY = 1,
	START_GAME,
	CHARECTER_SELECTION,
	TRACK_SELECTION,

	//Game
	RACE_START,
	RACE_OVER
};

enum ItemType
{
	NONE = -1,
	GREEN_SHELL = 0,
	RED_SHELL,
	BANANA,
	FAKE_BOX,
	MUSHROOM,
	MUSHROOM_3X,
	BOMB,
	BLUE_SHELL,
	LIGHTNING_BOLT,
	STAR,
	MUSHROOM_UNLIMITED,
	MUSHROOM_GIANT,
	SQUID,
	POW,
	LIGHTNING_CLOUD,
	BULLET_BILL,
	GREEN_SHELL_3X,
	RED_SHELL_3X,
	BANANA_3X
};

struct ItemBoxConfig {
	static double respawn_time;
};