#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "hero.h"
#include "Monster.h"
#include "GameMap.h"
namespace game_framework
{

Monster::Monster(int x, int y)
{
	Initialize(x, y);
}

void Monster::Initialize(int x, int y)
{
	SetXY(x, y);
	isAttack = false;
	isHurt = false;
	isSkill = false;
	isDead = false;
	ReallyDead = false;
	animation_hurt.SetDelayCount(3);
	animation_attack.SetDelayCount(2);
	animation_dead.SetDelayCount(5);
	LV = 0;
	gold = 43;
	xp = 14;
	currentBattleState = 0;
	countTime = 0;
	delay = false;
	playSoundEffect = false;
	DamageNum = Damage;
}

int Monster::GetX1()
{
	return x;
}

int Monster::GetY1()
{
	return y;
}

int Monster::GetX2()
{
	return x + animation_idle.Width();
}

int Monster::GetY2()
{
	return y + animation_idle.Height();
}

int Monster::GetAttackDamage()
{
	return Damage;
}

int Monster::GetGold()
{
	return gold;
}


int Monster::GetXp()
{
	return xp;
}

int Monster::GetHp()
{
	return _HP;
}

int Monster::GetCurrentBattleState()
{
	return currentBattleState;
}

void Monster::SetXY(int nx, int ny)
{
	x = nx;
	y = ny;
}

void Monster::SetHp(int HP)
{
	_HP = HP;
}

int Monster::GetFullHp()
{
	return FullHp;
}

void Monster::SetHurtDamage(bool flag)
{
	//設定怪物受傷
	isHurt = flag;
	currentBattleState = 2;
	animation_hurt.Reset();
}

void Monster::SetMonsterDelay(bool flag)
{
	delay = flag;
}

void Monster::StatusUpgrade(int hero_lv)
{
	//怪物會隨著主角的等級+-3等增強
	if (hero_lv >= 3)
	{
		if (hero_lv > 3)
		{
			int x = rand() % (7) - 3;
			LV = hero_lv + x;
		}

		FullHp = FullHp + 10 * LV;
		SetHp(FullHp);
		Damage = Damage + (int)(1.5 * LV);
	}
}
bool Monster::IsDead()
{
	//生命值歸0和死亡動畫結束
	return ReallyDead && _HP <= 0;
}

void Monster::OnMove()
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
		Skill();
		Dead();
	}
}

void Monster::AttackHero()
{
	isAttack = true;
	currentBattleState = 1;
	playSoundEffect = true;
	animation_attack.Reset();
	DamageNum = enemy->isGuarding() ? DamageNum / 2 : DamageNum - enemy->GetBlockDamage();
	DamageNum - enemy->GetBlockDamage() >= 0 ? DamageNum -= enemy->GetBlockDamage() : DamageNum = 0;
}

void Monster::SkillHero()
{
	/*多形物件的皮*/
	isSkill = true;
	currentBattleState = 3;
	playSoundEffect = true;
}

void Monster::Move()
{
	if (!isHurt && !isAttack && !isSkill && !isDead || delay)
		animation_idle.OnMove();
}

void Monster::Attack()
{
	if (isAttack && !isHurt && !isDead)
	{
		animation_attack.OnMove();

		if (animation_attack.IsFinalBitmap())
		{
			SetXY(-700, -400);
			enemy->GetHp() - DamageNum > 0 ?
			enemy->SetHp(enemy->GetHp() - DamageNum) : enemy->SetHp(0);
			currentBattleState = 0;
			isAttack = false;
		}
	}
}

void Monster::hurt()
{
	//怪物受傷動畫前置動作
	if (isHurt)
	{
		animation_hurt.OnMove();

		if (animation_hurt.IsFinalBitmap())
		{
			isHurt = false;

			if (_HP <= 0)
				isDead = true;

			delay = true;
		}
	}
}

void Monster::Dead()
{
	if (isDead && !isHurt)
	{
		animation_dead.OnMove();
		currentBattleState = 5;

		if (animation_dead.IsFinalBitmap())
		{
			currentBattleState = 0;
			isDead = false;
			ReallyDead = true;
		}
	}
}

void Monster::RandomDecision(Hero &hero)
{
	if (_HP <= 0)
	{
		isDead = true;
		animation_dead.Reset();
		return;
	}

	this->enemy = &hero;
	srand((unsigned)time(NULL));
	int max = 2;
	int rd = rand() % max;

	switch (rd)
	{
		case 0:
			AttackHero();
			break;

		case 1:
			SkillHero();
			break;

		default:
			break;
	}
}

void Monster::StopAMoment()
{
	if (countTime == 30)
	{
		countTime = 0;
		delay = false;
	}
	else
		countTime++;
}

void Monster::OnShow(AdjustableCInteger *NumberUI, CInteger *printNum, GameMap *map)
{
	AnimationMove(map);
	AnimationHurt(map);
	AnimationAttack(map);
	AnimationSkill(map);
	AnimationDead(map);
	ShowAttackDamage(NumberUI, map);
}

void Monster::AnimationMove(GameMap *map)
{
	if (!isHurt && !isAttack && !isSkill && !isDead || delay)
	{
		animation_idle.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_idle.OnShow();
	}
}

void Monster::ShowHp(int x1, int y1, int percent)
{
	percent = percent <= 0 ? 0 : percent;
	const int bar_width = 300;
	const int bar_height = 20;
	const int x2 = x1 + bar_width;
	const int y2 = y1 + bar_height;
	const int pen_width = bar_height / 8;
	const int progress_x1 = x1 + pen_width;
	const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / GetFullHp();
	const int progress_x2_end = x2 - pen_width;
	const int progress_y1 = y1 + pen_width;
	const int progress_y2 = y2 - pen_width;
	CDC *pDC = CDDraw::GetBackCDC();
	// 取得 Back Plain 的 CDC
	CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));
	// 清除pen
	pp = pDC->SelectObject(&p);
	CBrush *pb, b(RGB(0, 0, 0));
	pb = pDC->SelectObject(&b);
	pDC->Rectangle(x1, y1, x2, y2);
	CBrush b1(RGB(192, 192, 192));
	pDC->SelectObject(&b1);
	pDC->Rectangle(progress_x1, progress_y1, progress_x2_end, progress_y2);
	CBrush b2(RGB(132, 201, 160));
	pDC->SelectObject(&b2);
	pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
	pDC->SelectObject(pp);
	// 釋放 pen
	pDC->SelectObject(pb);
	// 釋放 brush
	CDDraw::ReleaseBackCDC();
	// 放掉 Back Plain 的 CDC
}

void Monster::ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map)
{
	if (animation_attack.GetCurrentBitmapNumber() >= 4 && isAttack)
	{
		// 攻擊動畫
		printNum->SetInteger(DamageNum);
		printNum->SetTopLeft(map->ScreenX(-1200 + 15), map->ScreenY(-400 - 100));
		printNum->ShowBitmap();
	}
}

void Monster::AnimationAttack(GameMap *map)
{
	if (isAttack && !isHurt && !delay)
	{
		animation_attack.SetTopLeft(map->ScreenX(-1200 + 158 / 2 - animation_attack.Width() / 2 - 10), map->ScreenY(-400 + 70 - animation_attack.Height()));
		animation_attack.OnShow();
	}
}

void Monster::AnimationHurt(GameMap *map)
{
	if (isHurt)
	{
		animation_hurt.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_hurt.OnShow();
	}
}

void Monster::AnimationSkill(GameMap *map)
{
}

void Monster::AnimationDead(GameMap *map)
{
	if (isDead && !isHurt && !delay)
	{
		animation_dead.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_dead.OnShow();
	}
}
}