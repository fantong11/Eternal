#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "GameMap.h"
#include "Item.h"
#include "Potion.h"

namespace game_framework
{
Potion::Potion() : Item(1, 50)
{
	heal_amount = 50;
	animation_effect.SetDelayCount(2);
	LoadBitmap();
}

void Potion::LoadBitmap()
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
	icon.LoadBitmap(IDB_POTION, RGB(255, 255, 255));
}

void Potion::Use(Hero *hero)
{
	int hp = hero->GetHp() + 50;
	hp = hp >= hero->GetMaxHp() ? hero->GetMaxHp() : hp;
	hero->SetHp(hp);
}
}