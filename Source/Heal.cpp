#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "GameMap.h"
#include "Skill.h"
#include "Heal.h"

namespace game_framework
{
Heal::Heal() : Skill(1, 20)
{
	x = -1200 - 105;
	y = -400 - 140;
	damage = -20;
	animation_effect.SetDelayCount(2);
	LoadBitmap();
}

void Heal::LoadBitmap()
{
	animation_effect.AddBitmap(IDB_HEALING_SPELL0, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL1, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL2, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL3, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL4, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL5, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL6, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL7, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL8, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL9, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL10, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEALING_SPELL11, RGB(0, 0, 0));
}
}