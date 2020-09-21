#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"
#include "Behemoth.h"
#include "BehemothSkill.h"
#include "ThunderClaw.h"

namespace game_framework
{
ThunderClaw::ThunderClaw() : BehemothSkill(42)
{
	LoadBitmap();
}
void ThunderClaw::LoadBitmap()
{
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC1, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC2, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC3, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC4, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC5, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC6, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC7, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC8, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC9, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC10, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK_ELECTIRC11, RGB(0, 0, 0));
}
}