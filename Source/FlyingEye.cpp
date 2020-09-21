#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "FlyingEye.h"
#include "Monster.h"
#include "Hero.h"
#include "GameMap.h"
#include "mygame.h"

namespace game_framework
{

FlyingEye::FlyingEye(int x, int y, int hero_lv) : Monster(x, y)
{
	FullHp = 66;
	_HP = 66;
	Damage = 19;
	Attack_1 = Attack_2 = Attack_3 = true;
	animation_idle.SetDelayCount(3);
	animation_skill.SetDelayCount(3);
	StatusUpgrade(hero_lv);
}

void FlyingEye::LoadBitmap()
{
	animation_idle.AddBitmap(IDB_FLYING_EYE_IDLE0, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_FLYING_EYE_IDLE1, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_FLYING_EYE_IDLE2, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_FLYING_EYE_IDLE3, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_FLYING_EYE_IDLE4, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_FLYING_EYE_IDLE5, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_FLYING_EYE_IDLE6, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_FLYING_EYE_IDLE7, RGB(255, 255, 255));
	animation_hurt.AddBitmap(IDB_FLYING_EYE_HURT0, RGB(0, 0, 0));
	animation_hurt.AddBitmap(IDB_FLYING_EYE_HURT1, RGB(0, 0, 0));
	animation_hurt.AddBitmap(IDB_FLYING_EYE_HURT2, RGB(0, 0, 0));
	animation_hurt.AddBitmap(IDB_FLYING_EYE_HURT3, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_FLYING_EYE_ATTACK0, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_FLYING_EYE_ATTACK1, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_FLYING_EYE_ATTACK2, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_FLYING_EYE_ATTACK3, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_FLYING_EYE_ATTACK4, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_FLYING_EYE_ATTACK5, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_FLYING_EYE_ATTACK6, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_FLYING_EYE_ATTACK7, RGB(255, 255, 255));
	animation_skill.AddBitmap(IDB_FLYING_EYE_SKILL5, RGB(255, 255, 255));
	animation_skill.AddBitmap(IDB_FLYING_EYE_SKILL6, RGB(255, 255, 255));
	animation_skill.AddBitmap(IDB_FLYING_EYE_SKILL7, RGB(255, 255, 255));
	animation_skill.AddBitmap(IDB_FLYING_EYE_ATTACK7, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_FLYING_EYE_DEAD0, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_FLYING_EYE_DEAD1, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_FLYING_EYE_DEAD2, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_FLYING_EYE_DEAD3, RGB(255, 255, 255));
}

void FlyingEye::StatusUpgrade(int hero_lv)
{
	Monster::StatusUpgrade(hero_lv);
	Damage += (int)(2 * LV);
}

void FlyingEye::AttackHero()
{
	DamageNum = Damage;
	Monster::AttackHero();
}

void FlyingEye::SkillHero()
//技能為發射BBB的光波對玩家造成3段傷害
{
	DamageNum = Damage + 14 * LV / 2;
	DamageNum /= 3;
	//傷害分段
	animation_attack.Reset();
	//因為沒完整的動畫，所以先用攻擊的來用
	animation_skill.Reset();
	DamageNum = enemy->isGuarding() ? DamageNum / 2 : DamageNum;
	DamageNum - enemy->GetBlockDamage() >= 0 ? DamageNum -= enemy->GetBlockDamage() : DamageNum = 0;
	Attack_1 = Attack_2 = Attack_3 = true;
	//傷害分段顯示的控制變數
	Monster::SkillHero();
}

void FlyingEye::Skill()
{
	if (isSkill && !isHurt && !isDead)
	{
		if (animation_attack.GetCurrentBitmapNumber() <= 4)
		{
			//前面先用攻擊動畫代替
			animation_attack.OnMove();
		}
		else
		{
			animation_skill.OnMove();

			//發射BBB光波
			if (playSoundEffect)
			{
				CAudio::Instance()->Play(AUDIO_LASER, false);
				playSoundEffect = false;
			}

			switch (animation_skill.GetCurrentBitmapNumber())
			{
				case 0:
					if (Attack_1)
					{
						//第一段傷害扣血
						enemy->GetHp() - DamageNum > 0 ?
						enemy->SetHp(enemy->GetHp() - DamageNum) : enemy->SetHp(0);
						Attack_1 = false;
					}

					break;

				case 1:
					if (Attack_2)
					{
						//第二段傷害扣血
						enemy->GetHp() - DamageNum > 0 ?
						enemy->SetHp(enemy->GetHp() - DamageNum) : enemy->SetHp(0);
						Attack_2 = false;
					}

					break;

				case 2:
					if (Attack_3)
					{
						//第三段傷害扣血
						enemy->GetHp() - DamageNum > 0 ?
						enemy->SetHp(enemy->GetHp() - DamageNum) : enemy->SetHp(0);
						Attack_3 = false;
					}

					break;
			}
		}

		if (animation_skill.IsFinalBitmap())
		{
			SetXY(-700, -400);
			currentBattleState = 0;
			isSkill = false;
		}
	}
}

void FlyingEye::AnimationSkill(GameMap *map)
{
	if (isSkill && !isHurt && !delay)
		//因為有用到2個動畫，所以都要設定
	{
		if (animation_attack.GetCurrentBitmapNumber() <= 4)
		{
			animation_attack.SetTopLeft(map->ScreenX(-1200 + animation_skill.Width() / 2), map->ScreenY(-400 + 70 - animation_skill.Height()));
			animation_attack.OnShow();
		}
		else
		{
			animation_skill.SetTopLeft(map->ScreenX(-1200 + 20), map->ScreenY(-400 + 70 - animation_skill.Height()));
			animation_skill.OnShow();
		}
	}
}

void FlyingEye::ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map)
{
	if (isSkill && animation_attack.GetCurrentBitmapNumber() > 4)
	{
		// 攻擊動畫
		if (!Attack_1)
		{
			//第一段的傷害顯示
			printNum->SetInteger(DamageNum);
			printNum->SetTopLeft(map->ScreenX(-1200 + 15), map->ScreenY(-400 - 160));
			printNum->ShowBitmap();
		}

		if (!Attack_2)
		{
			//第二段的傷害顯示
			printNum->SetInteger(DamageNum);
			printNum->SetTopLeft(map->ScreenX(-1200 + 15), map->ScreenY(-400 - 130));
			printNum->ShowBitmap();
		}

		if (!Attack_3)
		{
			//第三段的傷害顯示
			printNum->SetInteger(DamageNum);
			printNum->SetTopLeft(map->ScreenX(-1200 + 15), map->ScreenY(-400 - 100));
			printNum->ShowBitmap();
		}
	}

	Monster::ShowAttackDamage(printNum, map);
}
}