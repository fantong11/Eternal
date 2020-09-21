#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "Skill.h"
#include "GameMap.h"

namespace game_framework
{
Skill::Skill(int id, int manaCost)
{
	this->id = id;
	this->manaCost = manaCost;
}

int Skill::GetId()
{
	return id;
}

int Skill::GetManaCost()
{
	return manaCost;
}

int Skill::GetDamage()
{
	return damage;
}

bool Skill::AnimationIsFinalBitmap()
{
	return animation_effect.IsFinalBitmap();
}

void Skill::AnimationReset()
{
	animation_effect.Reset();
}


void Skill::OnMove()
{
	animation_effect.OnMove();
}

void Skill::OnShowEffect(GameMap *map)
{
	animation_effect.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
	animation_effect.OnShow();
}
}