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
	//�P�z��y��
	DamageNum = Damage * (LV - 2) / (LV);
	AttackTimes = 1;
	//���q�ˮ`
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
		//�b�L�������������񭵮�
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
			//�e�����Χ����ʵe�N��
			animation_attack.OnMove();

			if (animation_attack.IsFinalBitmap())
			{
				//�Ĥ@���������έ쥻������
				enemy->GetHp() - DamageNum > 0 ?
				enemy->SetHp(enemy->GetHp() - DamageNum) : enemy->SetHp(0);
				AttackTimes += 1;
				//�Ĥ@�q���������A�}�l���򪺧���
			}
		}
		else
		{
			animation_skill.OnMove();

			//�G�q�H�W�������}�l
			//�bskill�̭��ڳg�D��K�A�ҥH�⥪�k���䪺�ʳ���b�̭��A�ҥH��@�b���ɭԡA��@���������ơA�N�n����
			if (animation_skill.GetCurrentBitmapNumber() == 3 || animation_skill.IsFinalBitmap())
			{
				enemy->GetHp() - DamageNum > 0 ?
				enemy->SetHp(enemy->GetHp() - DamageNum) : enemy->SetHp(0);
				AttackTimes += 1;
				playSoundEffect = true;

				//���֤]�C��@�U�A�N���@��
				if (animation_skill.IsFinalBitmap())
					//���䳣�姹�A�A�~���A����姹����
					animation_skill.Reset();
			}
		}
	}

	if (playSoundEffect && (animation_attack.GetCurrentBitmapNumber() > 2 || animation_skill.GetCurrentBitmapNumber() > 0 || animation_skill.GetCurrentBitmapNumber() > 4))  		//�b�L�������������񭵮�
	{
		CAudio::Instance()->Play(AUDIO_SWORD, false);
		playSoundEffect = false;
	}

	if (AttackTimes == LV)
	{
		//�姹���Ƶ���
		SetXY(-700, -400);
		currentBattleState = 0;
		isSkill = false;
	}
}

void Goblin::AnimationSkill(GameMap *map)
//���쥻�������ʵe�����k�䪺�ʵe
{
	if (isSkill && !isHurt && !delay)
		//�쥻�������ʵe
	{
		if (AttackTimes == 1)
		{
			animation_attack.SetTopLeft(map->ScreenX(-1200 + 158 / 2 - animation_attack.Width() / 2 - 10), map->ScreenY(-400 + 70 - animation_attack.Height()));
			animation_attack.OnShow();
		}
		else
		{
			//�ޯ�ʵe
			AttackTimes % 2 == 0 ?
			//�ھڥثe���������ƧP�_���k��
			animation_skill.SetTopLeft(map->ScreenX(-1200 - 100), map->ScreenY(-400 + 70 - animation_skill.Height())) :		//����ޯ��m
			animation_skill.SetTopLeft(map->ScreenX(-1200 + 158 / 2 - animation_skill.Width() / 2 - 10), map->ScreenY(-400 + 70 - animation_skill.Height()));		//�k��ޯ��m
			animation_skill.OnShow();
		}
	}
}

void Goblin::ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map)
{
	int time = AttackTimes - 1;

	if (isSkill && (animation_attack.GetCurrentBitmapNumber() > 4 || animation_skill.GetCurrentBitmapNumber() > 0))   // �����ʵe
	{
		while (time >= 0)
		{
			//�ھڥثe���������ƨM�w��ܶ���
			printNum->SetInteger(DamageNum);
			printNum->SetTopLeft(map->ScreenX(-1225 + 90 * int(pow(double(-1), double(time)))), map->ScreenY(-400 - 100 - 15 * time));
			printNum->ShowBitmap();
			time--;
		}
	}

	Monster::ShowAttackDamage(printNum, map);
}
}