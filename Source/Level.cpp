#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Level.h"
namespace game_framework
{
Level::Level()
{
	lv = xp = 0;
	requireXp = 0;
}

int Level::GetLv()
{
	return lv;
}

int Level::GetXp()
{
	return xp;
}

int Level::GetRequireXp()
{
	return requireXp;
}

void Level::SetLv(int lv)
{
	this->lv = lv;
}

void Level::SetXp(int xp)
{
	this->xp = xp;
}

void Level::SetRequireXp()
{
	if (lv < 16)
		requireXp += 2 * lv + 7;
	else if (lv < 32)
		requireXp += 5 * lv - 38;
	else
		requireXp += 9 * lv - 158;
}
}