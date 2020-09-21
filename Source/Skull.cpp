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
		//計算提升後傷害
		DamageNum += 20;
		nextAttackBuff --;
	}

	Monster::AttackHero();
}

void Skull::SkillHero()
{
	//技能為下一次攻擊提升傷害，可ˇ疊加
	Monster::SkillHero();
	nextAttackBuff += 1;
	//提升一次
	currentBattleState = 0;
	//因為沒有動畫所以直接關掉
	playSoundEffect = false;
	//同上
}

void Skull::Attack()
{
	Monster::Attack();

	if (playSoundEffect && animation_attack.GetCurrentBitmapNumber() > 2)
	{
		//在他揮刀的瞬間撥放音效
		CAudio::Instance()->Play(AUDIO_SWORD, false);
		playSoundEffect = false;
		isSkill = false;
	}
}

void Skull::Skill()
{
	/*動畫放的地方*/
}

void Skull::printBuff()
{
	//print出使用技能
	if (isSkill && !delay && !isHurt && !isAttack && !isDead)
	{
		CDC *pDC = CDDraw::GetBackCDC();
		// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(300, "Microsoft JhengHei");
		// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);
		// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		char str[80];
		// Demo 數字對字串的轉換
		sprintf(str, "蓄力x%d", nextAttackBuff);
		pDC->TextOut(700, 210, str);
		pDC->SelectObject(fp);
		// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();
		// 放掉 Back Plain 的 CDC
	}
}

void Skull::OnShow(AdjustableCInteger *NumberUI, CInteger *printNum, GameMap *map)
{
	Monster::OnShow(NumberUI, printNum, map);
	printBuff();
}

void Skull::AnimationMove(GameMap *map)
{
	//為了讓文字可以正常print出來這裡要小修改
	if (!isHurt && !isAttack && !isDead || delay)
	{
		animation_idle.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_idle.OnShow();
	}
}
}