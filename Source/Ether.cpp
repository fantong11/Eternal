#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "GameMap.h"
#include "Item.h"
#include "Ether.h"

namespace game_framework
{
Ether::Ether() : Item(2, 87)
{
	heal_amount = 50;
	animation_effect.SetDelayCount(2);
	LoadBitmap();
}

void Ether::LoadBitmap()
{
	animation_effect.AddBitmap(IDB_HEAL_MANA0, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA1, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA2, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA3, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA4, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA5, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA6, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA7, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA8, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA9, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA10, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA11, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA12, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA13, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA14, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA15, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA16, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA17, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA18, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA19, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA20, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA21, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA22, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA23, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA24, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA25, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA26, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA27, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA28, RGB(0, 0, 0));
	animation_effect.AddBitmap(IDB_HEAL_MANA29, RGB(0, 0, 0));
}

void Ether::Use(Hero *hero)
{
	int mp = hero->GetMp() + 50;
	mp >= hero->GetMaxMp() ? hero->SetMp(hero->GetMaxMp()) : hero->SetMp(mp);
}

void Ether::OnShowEffect(int x, int y)
{
	animation_effect.SetTopLeft(x + 30, y + 40);
	animation_effect.OnShow();
}

void Ether::OnShowIcon(int x, int y)
{
	// ªÅªº
}
}