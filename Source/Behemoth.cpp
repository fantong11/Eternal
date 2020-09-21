#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <memory>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "IceClaw.h"
#include "FireClaw.h"
#include "ThunderClaw.h"
#include "BehemothSkill.h"
#include "Behemoth.h"
#include "Hero.h"
#include <iostream>
#include "mygame.h"
using namespace std;

namespace game_framework
{
Behemoth::Behemoth() : Monster(-850, -525)
{
	this->FullHp = 543;
	SetHp(FullHp);
	this->Damage = 81;
	isSkill = false;
	skillId = 0;
	rush = -2;
	skills.push_back(make_unique<IceClaw>());
	skills.push_back(make_unique<FireClaw>());
	skills.push_back(make_unique<ThunderClaw>());
}

void Behemoth::LoadBitmap()
{
	animation_idle.AddBitmap(IDB_BEHEMOTH, RGB(255, 255, 255));
	animation_hurt.AddBitmap(IDB_BEHEMOTH, RGB(255, 255, 255));
	animation_hurt.AddBitmap(IDB_BEHEMOTH, RGB(255, 255, 255));
	animation_hurt.AddBitmap(IDB_BEHEMOTH, RGB(255, 255, 255));
	animation_hurt.AddBitmap(IDB_BEHEMOTH, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_BEHEMOTH, RGB(255, 255, 255));
}

void Behemoth::OnMove()
{
	if (delay)
	{
		StopAMoment();
		Move();
	}
	else
	{
		Move();
		hurt();
		Attack();
		Dead();
	}
}

void Behemoth::RandomDecision(Hero &hero)
{
	if (_HP <= 0)
	{
		isDead = true;
		animation_dead.Reset();
		return;
	}

	this->enemy = &hero;
	srand((unsigned)time(NULL));
	int max = 3;
	int rd = rand() % max;

	switch (rd)
	{
		//隨機選擇施放的技能
		case 0:
			skillId = 0;
			break;

		case 1:
			skillId = 1;
			break;

		case 2:
			skillId = 2;
			break;

		default:
			break;
	}

	AttackHero();
}

void Behemoth::Attack()
{
	if (isAttack && !isHurt && !isDead)
	{
		if (rush > 100)
			skills[skillId]->OnMove();

		if (rush < -50)
			rush = 2;

		rush += rush;

		if (skills[skillId]->AnimationIsFinalBitmap())
		{
			SetXY(-850, -525);
			rush = -2;
			enemy->GetHp() - DamageNum > 0 ?
			enemy->SetHp(enemy->GetHp() - DamageNum) : enemy->SetHp(0);
			currentBattleState = 0;
			isAttack = false;
		}

		if (playSoundEffect && skills[skillId]->GetCurrentBitmapNumber() > 2)
		{
			CAudio::Instance()->Play(AUDIO_SWORD, false);
			playSoundEffect = false;
		}
	}
}

void Behemoth::Skill()
{
	//空的
}

void Behemoth::hurt()
{
	if (isHurt)
	{
		animation_hurt.OnMove();

		if (animation_hurt.IsFinalBitmap())
		{
			isHurt = false;
			SetXY(-850, -525);

			if (_HP <= 0)
				isDead = true;

			delay = true;
		}
	}
}

void Behemoth::AttackHero()
{
	DamageNum = Damage;
	isAttack = true;
	currentBattleState = 1;
	playSoundEffect = true;
	skills[skillId]->AnimationReset();
	DamageNum = enemy->isGuarding() ? DamageNum / 2 : DamageNum - enemy->GetBlockDamage();
	DamageNum - enemy->GetBlockDamage() >= 0 ? DamageNum -= enemy->GetBlockDamage() : DamageNum = 0;
}

void Behemoth::OnShow(AdjustableCInteger *NumberUI, CInteger *printNum, GameMap *map)
{
	AnimationMove(map);
	AnimationHurt(map);
	AnimationAttack(map);
	AnimationDead(map);
	ShowAttackDamage(NumberUI, map);
}

void Behemoth::AnimationAttack(GameMap *map)
{
	if (isAttack && !isHurt && !delay && rush > 100)
	{
		skills[skillId]->OnShow(map);
	}
}

void Behemoth::ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map)
{
	if (skills[skillId]->GetCurrentBitmapNumber() >= 4 && isAttack)
	{
		// 當攻擊動畫進行到揮爪時才顯示傷害數字
		printNum->SetInteger(DamageNum);
		printNum->SetTopLeft(map->ScreenX(-1200 + 15), map->ScreenY(-400 - 100));
		printNum->ShowBitmap();
	}
}

void Behemoth::AnimationHurt(GameMap *map)
{
	if (isHurt)
	{
		animation_hurt.SetTopLeft(map->ScreenX(x + 50), map->ScreenY(y));
		animation_hurt.OnShow();
	}
}

void Behemoth::AnimationMove(GameMap *map)
{
	if (!isHurt && !isAttack && !isDead || delay)
	{
		animation_idle.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_idle.OnShow();
	}

	if (isAttack && !delay && !isHurt)
	{
		animation_idle.SetTopLeft(map->ScreenX(x - rush), map->ScreenY(y));
		animation_idle.OnShow();
	}
}
}