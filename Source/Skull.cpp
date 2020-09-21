#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Skull.h"
#include "Monster.h"
#include "GameMap.h"
#include "mygame.h"

namespace game_framework
{

Skull::Skull(int x, int y, int hero_lv) : Monster(x, y)
{
	FullHp = 87;
	_HP = 87;
	Damage = 16;
	nextAttackBuff = 0;
	animation_idle.SetDelayCount(6);
	StatusUpgrade(hero_lv);
}

void Skull::LoadBitmap()
{
	animation_idle.AddBitmap(IDB_SKULL_IDLE0, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_SKULL_IDLE1, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_SKULL_IDLE2, RGB(255, 255, 255));
	animation_idle.AddBitmap(IDB_SKULL_IDLE3, RGB(255, 255, 255));
	animation_hurt.AddBitmap(IDB_SKULL_HURT0, RGB(0, 0, 0));
	animation_hurt.AddBitmap(IDB_SKULL_HURT1, RGB(0, 0, 0));
	animation_hurt.AddBitmap(IDB_SKULL_HURT2, RGB(0, 0, 0));
	animation_hurt.AddBitmap(IDB_SKULL_HURT3, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_SKULL_ATTACK0, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_SKULL_ATTACK1, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_SKULL_ATTACK2, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_SKULL_ATTACK3, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_SKULL_ATTACK4, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_SKULL_ATTACK5, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_SKULL_ATTACK6, RGB(0, 0, 0));
	animation_attack.AddBitmap(IDB_SKULL_ATTACK7, RGB(0, 0, 0));
	animation_dead.AddBitmap(IDB_SKULL_DEAD0, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_SKULL_DEAD1, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_SKULL_DEAD2, RGB(255, 255, 255));
	animation_dead.AddBitmap(IDB_SKULL_DEAD3, RGB(255, 255, 255));
}

void Skull::StatusUpgrade(int hero_lv)
{
	Monster::StatusUpgrade(hero_lv);
	FullHp += (int)(10 * hero_lv);
	SetHp(FullHp);
	Damage += (int)(5 * hero_lv);
}


void Skull::AttackHero()
{
	DamageNum = Damage;

	while (nextAttackBuff > 0)
	{
		//�p�ⴣ�ɫ�ˮ`
		DamageNum += 20;
		nextAttackBuff --;
	}

	Monster::AttackHero();
}

void Skull::SkillHero()
{
	//�ޯର�U�@���������ɶˮ`�A�i���|�[
	Monster::SkillHero();
	nextAttackBuff += 1;
	//���ɤ@��
	currentBattleState = 0;
	//�]���S���ʵe�ҥH��������
	playSoundEffect = false;
	//�P�W
}

void Skull::Attack()
{
	Monster::Attack();

	if (playSoundEffect && animation_attack.GetCurrentBitmapNumber() > 2)
	{
		//�b�L���M���������񭵮�
		CAudio::Instance()->Play(AUDIO_SWORD, false);
		playSoundEffect = false;
		isSkill = false;
	}
}

void Skull::Skill()
{
	/*�ʵe�񪺦a��*/
}

void Skull::printBuff()
{
	//print�X�ϥΧޯ�
	if (isSkill && !delay && !isHurt && !isAttack && !isDead)
	{
		CDC *pDC = CDDraw::GetBackCDC();
		// ���o Back Plain �� CDC
		CFont f, *fp;
		f.CreatePointFont(300, "Microsoft JhengHei");
		// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);
		// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		char str[80];
		// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, "�W�Ox%d", nextAttackBuff);
		pDC->TextOut(700, 210, str);
		pDC->SelectObject(fp);
		// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();
		// �� Back Plain �� CDC
	}
}

void Skull::OnShow(AdjustableCInteger *NumberUI, CInteger *printNum, GameMap *map)
{
	Monster::OnShow(NumberUI, printNum, map);
	printBuff();
}

void Skull::AnimationMove(GameMap *map)
{
	//���F����r�i�H���`print�X�ӳo�̭n�p�ק�
	if (!isHurt && !isAttack && !isDead || delay)
	{
		animation_idle.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_idle.OnShow();
	}
}
}