#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "GameMap.h"
#include "Skill.h"
#include "Lightning.h"

namespace game_framework
{
Lightning::Lightning() : Skill(0, 12)
{
	x = -750;
	y = -430;
	damage = 9;
	animation_effect.SetDelayCount(1);
	LoadBitmap();
}

void Lightning::LoadBitmap()
{
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL0, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL1, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL2, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL3, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL4, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL5, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL6, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL7, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL8, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL9, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL10, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_LIGHTNING_SPELL11, RGB(0, 0, 0));
}
}