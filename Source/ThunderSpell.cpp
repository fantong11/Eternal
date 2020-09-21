#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "GameMap.h"
#include "Skill.h"
#include "ThunderSpell.h"

namespace game_framework
{
ThunderSpell::ThunderSpell() : Skill(2, 10)
{
	x = -750;
	y = -430;
	damage = 5;
	animation_effect.SetDelayCount(2);
	LoadBitmap();
}
void ThunderSpell::LoadBitmap()
{
	animation_effect.AddBitmap(IDB_THUNDER_SPELL0, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_THUNDER_SPELL1, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_THUNDER_SPELL2, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_THUNDER_SPELL3, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_THUNDER_SPELL4, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_THUNDER_SPELL5, RGB(0, 0, 0));
}
}