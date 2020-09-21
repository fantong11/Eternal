#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "GameMap.h"
#include "BehemothSkill.h"

namespace game_framework
{

BehemothSkill::BehemothSkill(int damage)
{
	this->damage = damage;
	effect.SetDelayCount(2);
}

int BehemothSkill::GetDamage()
{
	return damage;
}

int BehemothSkill::GetCurrentBitmapNumber()
{
	return effect.GetCurrentBitmapNumber();
}

bool BehemothSkill::AnimationIsFinalBitmap()
{
	return effect.IsFinalBitmap();
}

void BehemothSkill::AnimationReset()
{
	effect.Reset();
}


void BehemothSkill::OnMove()
{
	effect.OnMove();
}

void BehemothSkill::OnShow(GameMap *map)
{
	effect.SetTopLeft(map->ScreenX(-1250), map->ScreenY(-480));
	effect.OnShow();
}
}