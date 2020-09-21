#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"
#include "Behemoth.h"
#include "BehemothSkill.h"
#include "FireClaw.h"

namespace game_framework
{
FireClaw::FireClaw() : BehemothSkill(42)
{
	LoadBitmap();
}
void FireClaw::LoadBitmap()
{
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK1, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK2, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK3, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK4, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK5, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK6, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK7, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK8, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK9, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK10, RGB(0, 0, 0));
	effect.AddBitmap(IDB_BEHEMOTH_ATTACK11, RGB(0, 0, 0));
}
}