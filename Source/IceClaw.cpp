#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"
#include "Behemoth.h"
#include "BehemothSkill.h"
#include "IceClaw.h"

namespace game_framework
{
IceClaw::IceClaw() : BehemothSkill(42)
{
	LoadBitmap();
}
void IceClaw::LoadBitmap()
{
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE1, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE2, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE3, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE4, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE5, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE6, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE7, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE8, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE9, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE10, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ICE11, RGB(0, 0, 0));
}
}