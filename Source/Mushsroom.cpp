#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Mushsroom.h"
#include "Monster.h"
#include "Hero.h"
#include "GameMap.h"
#include "mygame.h"

namespace game_framework
{

Mushsroom::Mushsroom(int x, int y, int hero_lv) : Monster(x, y)
{
	FullHp = 100;
	_HP = 100;
	Damage = 12;
	animation_idle.SetDelayCount(6);
	StatusUpgrade(hero_lv);
}

void Mushsroom::LoadBitmap()
{
	animation_idle.AddBitmap(IDB_MUSHSROOM_IDLE0, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_MUSHSROOM_IDLE1, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_MUSHSROOM_IDLE2, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_MUSHSROOM_IDLE3, RGB(255, 255, 255));
	animation_hurt.AddBitmap(IDB_MUSHROOM_HURT0, RGB(0, 0, 0));
	animation_hurt.AddBitmap(IDB_MUSHROOM_HURT1, RGB(0, 0, 0));
	animation_hurt.AddBitmap(IDB_MUSHROOM_HURT2, RGB(0, 0, 0));
	animation_hurt.AddBitmap(IDB_MUSHROOM_HURT3, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_MUSHROOM_ATTACK0, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_MUSHROOM_ATTACK1, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_MUSHROOM_ATTACK2, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_MUSHROOM_ATTACK3, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_MUSHROOM_ATTACK4, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_MUSHROOM_ATTACK5, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_MUSHROOM_ATTACK6, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_MUSHROOM_ATTACK7, RGB(0, 0, 0));
	animation_dead.AddBitmap(IDB_MUSHSROOM_DEAD0, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_MUSHSROOM_DEAD1, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_MUSHSROOM_DEAD2, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_MUSHSROOM_DEAD3, RGB(255, 255, 255));
}

void Mushsroom::StatusUpgrade(int hero_lv)
{
	Monster::StatusUpgrade(hero_lv);
	FullHp = FullHp + (int)(FullHp * 0.25);
	SetHp(FullHp);
}


void Mushsroom::AttackHero()
{
	DamageNum = Damage;
	Monster::AttackHero();
}

void Mushsroom::SkillHero()
{
	//技能為施放無法阻擋的吸血攻擊
	DamageNum = Damage - 5;
	animation_attack.Reset();
	//因為沒動畫所以先用攻擊的動畫
	Monster::SkillHero();
}

void Mushsroom::Attack()
{
	Monster::Attack();

	if (playSoundEffect && animation_attack.GetCurrentBitmapNumber() > 2)
	{
		//在他打擊的瞬間撥放音效
		CAudio::Instance()->Play(AUDIO_HIT, false);
		playSoundEffect = false;
	}
}

void Mushsroom::Skill()
{
	if (isSkill && !isHurt && !isDead)
	{
		animation_attack.OnMove();

		if (animation_attack.IsFinalBitmap())
		{
			SetXY(-700, -400);
			enemy->GetHp() - DamageNum > 0 ?
			enemy->SetHp(enemy->GetHp() - DamageNum) : enemy->SetHp(0);
			currentBattleState = 0;
			isSkill = false;
			_HP + DamageNum >= FullHp ? SetHp(FullHp) : SetHp(_HP + DamageNum);
		}
	}

	if (playSoundEffect && animation_attack.GetCurrentBitmapNumber() > 2)
	{
		//在他打擊的瞬間撥放音效
		CAudio::Instance()->Play(AUDIO_HIT, false);
		playSoundEffect = false;
	}
}

void Mushsroom::AnimationSkill(GameMap *map)
{
	if (isSkill && !isHurt && !delay)
	{
		animation_attack.SetTopLeft(map->ScreenX(-1200 + 158 / 2 - animation_attack.Width() / 2 - 10), map->ScreenY(-400 + 70 - animation_attack.Height()));
		animation_attack.OnShow();
	}
}

void Mushsroom::ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map)
{
	if (isSkill && animation_attack.GetCurrentBitmapNumber() > 4)
	{
		// 攻擊動畫
		printNum->SetInteger(DamageNum);
		printNum->SetTopLeft(map->ScreenX(-1200 + 15), map->ScreenY(-400 - 100));
		printNum->ShowBitmap();
	}

	Monster::ShowAttackDamage(printNum, map);
}
}