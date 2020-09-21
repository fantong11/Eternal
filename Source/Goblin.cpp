#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Goblin.h"
#include "Monster.h"
#include "GameMap.h"
#include "mygame.h"

namespace game_framework
{

Goblin::Goblin(int x, int y, int hero_lv) : Monster(x, y)
{
	FullHp = 72;
	_HP = 72;
	Damage = 14;
	AttackTimes = 0;
	animation_idle.SetDelayCount(3);
	animation_skill.SetDelayCount(1);
	StatusUpgrade(hero_lv);
}

void Goblin::LoadBitmap()
{
	animation_idle.AddBitmap(IDB_GOBLIN_IDLE0, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_GOBLIN_IDLE1, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_GOBLIN_IDLE2, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_GOBLIN_IDLE3, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_GOBLIN_IDLE2, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_GOBLIN_IDLE1, RGB(255, 255, 255));
	animation_hurt.AddBitmap(IDB_GOBLIN_HURT0, RGB(255, 255, 255));
	animation_hurt.AddBitmap(IDB_GOBLIN_HURT1, RGB(0, 0, 0));
	animation_hurt.AddBitmap(IDB_GOBLIN_HURT2, RGB(255, 255, 255));
	animation_hurt.AddBitmap(IDB_GOBLIN_HURT3, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_GOBLIN_ATTACK0, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_GOBLIN_ATTACK1, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_GOBLIN_ATTACK2, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_GOBLIN_ATTACK3, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_GOBLIN_ATTACK4, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_GOBLIN_ATTACK5, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_GOBLIN_ATTACK6, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_GOBLIN_ATTACK7, RGB(0, 0, 0));
	animation_skill.AddBitmap(IDB_GOBLIN_SKILL0, RGB(0, 0, 0));
	animation_skill.AddBitmap(IDB_GOBLIN_SKILL1, RGB(0, 0, 0));
	animation_skill.AddBitmap(IDB_GOBLIN_SKILL2, RGB(0, 0, 0));
	animation_skill.AddBitmap(IDB_GOBLIN_SKILL3, RGB(0, 0, 0));
	animation_skill.AddBitmap(IDB_GOBLIN_ATTACK4, RGB(0, 0, 0));
	animation_skill.AddBitmap(IDB_GOBLIN_ATTACK5, RGB(0, 0, 0));
	animation_skill.AddBitmap(IDB_GOBLIN_ATTACK6, RGB(0, 0, 0));
	animation_skill.AddBitmap(IDB_GOBLIN_ATTACK7, RGB(0, 0, 0));
	animation_dead.AddBitmap(IDB_GOBLIN_DEAD0, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_GOBLIN_DEAD1, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_GOBLIN_DEAD2, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_GOBLIN_DEAD3, RGB(255, 255, 255));
}

void Goblin::StatusUpgrade(int hero_lv)
{
	Monster::StatusUpgrade(hero_lv);
	FullHp = FullHp + 2 * LV;
	SetHp(FullHp);
	Damage += (int)(1 * LV);
	LV <= 4 ? LV = 4 : LV = LV ;
}

void Goblin::AttackHero()
{
	DamageNum = Damage;
	Monster::AttackHero();
}

void Goblin::SkillHero()
{
	//星爆氣流斬
	DamageNum = Damage * (LV - 2) / (LV);
	AttackTimes = 1;
	//分段傷害
	animation_attack.Reset();
	animation_skill.Reset();
	DamageNum = enemy->isGuarding() ? DamageNum / 2 : DamageNum;
	Monster::SkillHero();
	DamageNum - enemy->GetBlockDamage() >= 0 ? DamageNum -= enemy->GetBlockDamage() : DamageNum = 0;
}

void Goblin::Attack()
{
	Monster::Attack();

	if (playSoundEffect && animation_attack.GetCurrentBitmapNumber() > 3)
	{
		//在他打擊的瞬間撥放音效
		CAudio::Instance()->Play(AUDIO_SWORD, false);
		playSoundEffect = false;
	}
}

void Goblin::Skill()
{
	if (isSkill && !isHurt && !isDead)
	{
		if (AttackTimes == 1)
		{
			//前面先用攻擊動畫代替
			animation_attack.OnMove();

			if (animation_attack.IsFinalBitmap())
			{
				//第一次攻擊先用原本的攻擊
				enemy->GetHp() - DamageNum > 0 ?
				enemy->SetHp(enemy->GetHp() - DamageNum) : enemy->SetHp(0);
				AttackTimes += 1;
				//第一段攻擊結束，開始後續的攻擊
			}
		}
		else
		{
			animation_skill.OnMove();

			//二段以上的攻擊開始
			//在skill裡面我貪求方便，所以把左右兩邊的動都放在裡面，所以到一半的時候，算一次攻擊次數，就要換邊
			if (animation_skill.GetCurrentBitmapNumber() == 3 || animation_skill.IsFinalBitmap())
			{
				enemy->GetHp() - DamageNum > 0 ?
				enemy->SetHp(enemy->GetHp() - DamageNum) : enemy->SetHp(0);
				AttackTimes += 1;
				playSoundEffect = true;

				//音樂也每砍一下，就撥一次
				if (animation_skill.IsFinalBitmap())
					//兩邊都砍完，再繼續砍，直到砍完次數
					animation_skill.Reset();
			}
		}
	}

	if (playSoundEffect && (animation_attack.GetCurrentBitmapNumber() > 2 || animation_skill.GetCurrentBitmapNumber() > 0 || animation_skill.GetCurrentBitmapNumber() > 4))  		//在他砍擊的瞬間撥放音效
	{
		CAudio::Instance()->Play(AUDIO_SWORD, false);
		playSoundEffect = false;
	}

	if (AttackTimes == LV)
	{
		//砍完次數結束
		SetXY(-700, -400);
		currentBattleState = 0;
		isSkill = false;
	}
}

void Goblin::AnimationSkill(GameMap *map)
//有原本的攻擊動畫跟左邊跟右邊的動畫
{
	if (isSkill && !isHurt && !delay)
		//原本的攻擊動畫
	{
		if (AttackTimes == 1)
		{
			animation_attack.SetTopLeft(map->ScreenX(-1200 + 158 / 2 - animation_attack.Width() / 2 - 10), map->ScreenY(-400 + 70 - animation_attack.Height()));
			animation_attack.OnShow();
		}
		else
		{
			//技能動畫
			AttackTimes % 2 == 0 ?
			//根據目前的攻擊次數判斷左右邊
			animation_skill.SetTopLeft(map->ScreenX(-1200 - 100), map->ScreenY(-400 + 70 - animation_skill.Height())) :		//左邊技能位置
			animation_skill.SetTopLeft(map->ScreenX(-1200 + 158 / 2 - animation_skill.Width() / 2 - 10), map->ScreenY(-400 + 70 - animation_skill.Height()));		//右邊技能位置
			animation_skill.OnShow();
		}
	}
}

void Goblin::ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map)
{
	int time = AttackTimes - 1;

	if (isSkill && (animation_attack.GetCurrentBitmapNumber() > 4 || animation_skill.GetCurrentBitmapNumber() > 0))   // 攻擊動畫
	{
		while (time >= 0)
		{
			//根據目前的攻擊次數決定顯示順序
			printNum->SetInteger(DamageNum);
			printNum->SetTopLeft(map->ScreenX(-1225 + 90 * int(pow(double(-1), double(time)))), map->ScreenY(-400 - 100 - 15 * time));
			printNum->ShowBitmap();
			time--;
		}
	}

	Monster::ShowAttackDamage(printNum, map);
}
}