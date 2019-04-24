#pragma once
#include <vector>

/*

	!!!		DO NOT REORDER ANY OF THESE ENUMS!		!!!

*/

enum Scenes
{
	MENUSCENE,
	DEBUG_LIGHTINGTEST,
	GAMESCENE, // must be second to last as we dynamically extend from this position

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
	BANANA_3X,

	PLACEHOLDER //This isn't an item - is used as the placeholder UI sprite. Do not call unless for that use case.
};


struct ItemBoxConfig {
	static double respawn_time;
};

// camera type

enum class CameraType : int
{
	FOLLOW = 0,
	BACK_FACING = 1,
	FIRST = 2,
	INDEPENDENT = 3,
	ORBIT = 4,
	CINEMATIC = 5,
#ifdef _DEBUG
	DEBUG_CAM = 6,
#endif
};


// sound
// sound catergories
enum class SOUND_TYPE : int
{
	MENU = 0,
	GAME = 1,
	CHARACTER_SEL = 2,
	MISC = 3,
};

// game sounds
enum class SOUNDS_GAME : int
{
	MKS_START = 0,
	MKS_GAME = 1,
	MKS_FL_START = 2,
	MKS_FL_GAME = 3
};

// character sounds
enum class SOUNDS_CHARACTER : int
{
	MARIO = 0,
	BOWSER = 1,
	PEACH = 2,
	WALUIGI = 3,
};

// menu sounds
enum class SOUNDS_MENU : int
{
	MENU_LOOP = 0,
	TITLE_START = 1,
	TTLE_LOOP = 2,
};

// misc sounds
enum class SOUNDS_MISC : int
{
	INTRO_MUSIC = 0,
	PRE_COUNTDOWN = 1,
	COUNTDOWN = 2,
	ITEM_BOX_HIT = 3,
	FINAL_LAP_IND = 4,
};