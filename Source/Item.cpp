#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "Item.h"
#include "GameMap.h"

namespace game_framework
{
Item::Item(int id, int amount)
{
	this->id = id;
	this->amount = amount;
}

int Item::GetId()
{
	return id;
}

int Item::GetAmount()
{
	return amount;
}

int Item::GetCurrentBitmapNumber()
{
	return animation_effect.GetCurrentBitmapNumber();
}

void Item::SetItemAmount(int amount)
{
	this->amount = amount;
}

bool Item::AnimationIsFinalBitmap()
{
	return animation_effect.IsFinalBitmap();
}

void Item::AnimationReset()
{
	animation_effect.Reset();
}

void Item::OnMove()
{
	animation_effect.OnMove();
}

void Item::OnShowEffect(int x, int y)
{
	animation_effect.SetTopLeft(x, y);
	animation_effect.OnShow();
}

void Item::OnShowIcon(int x, int y)
{
	icon.SetTopLeft(x, y);
	icon.ShowBitmap();
}
}