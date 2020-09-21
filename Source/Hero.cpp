#include <cstdlib>
#include <ctime>
#include <math.h>
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Skull.h"
#include "Hero.h"
#include "Level.h"
#include "Potion.h"
#include "Ether.h"
#include "Item.h"
#include "Lightning.h"
#include "Heal.h"
#include "ThunderSpell.h"
#include "Skill.h"
#include "GameMap.h"
#include "mygame.h"
#define BAR_WIDTH 300
#define BAR_HEIGHT 25
namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// Hero: hero class
/////////////////////////////////////////////////////////////////////////////

Hero::Hero()
{
	//Initialize();
}

void Hero::Initialize(bool *isBattling, vector<unique_ptr<Npc>> *npc, vector<unique_ptr<Chest>> *chest)
{
	const int X_POS = 360;
	const int Y_POS = 420;
	x = X_POS;
	y = Y_POS;
	STEP_SIZE = 5;
	RUN_SIZE = 10;
	Gold = 100;
	itemId = 0;
	skillId = 0;
	weapon_grade = 1;
	armor_grade = 1;
	shield_grade = 1;
	blockDamage = 0;
	treasure = 0;
	finally_chest = 0;
	level.SetLv(1);
	level.SetRequireXp();
	isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	lastMovingState = 3;
	// 初始面向下面
	_isBattling = isBattling;
	isRunning = false;
	_HP = MaxHp = 100;
	_MP = MaxMp = 100;
	AttackDamage = 24;
	SkillDamage = 28;
	isAttack = false;
	isGuard = false;
	isHeal = false;
	isSkill = false;
	isPressEnter = false;
	//現在沒有再開寶箱
	isInFrontOfBoss_door = false;
	readllyFight = false;
	moveDistance = 0;
	currentBattleState = 0;
	this->npc = npc;
	this->chest = chest;
	items.push_back(make_unique<Potion>());
	items[0]->SetItemAmount(5);
	items.push_back(make_unique<Ether>());
	items[1]->SetItemAmount(5);
	skills.push_back(make_unique<Lightning>());
	skills.push_back(make_unique<Heal>());
	skills.push_back(make_unique<ThunderSpell>());
	animation_U.SetDelayCount(5);
	animation_D.SetDelayCount(5);
	animation_L.SetDelayCount(5);
	animation_R.SetDelayCount(5);
	animation_attack.SetDelayCount(3);
	animation_guard.SetDelayCount(8);
}

void Hero::LoadBitmap()
{
	animation_U.AddBitmap(IDB_HERO_UP_WALK0, RGB(255, 255, 255));
	animation_U.AddBitmap(IDB_HERO_UP_WALK1, RGB(255, 255, 255));
	animation_U.AddBitmap(IDB_HERO_UP_WALK2, RGB(255, 255, 255));
	animation_U.AddBitmap(IDB_HERO_UP_WALK3, RGB(255, 255, 255));
	animation_D.AddBitmap(IDB_HERO_DOWN_WALK0, RGB(255, 255, 255));
	animation_D.AddBitmap(IDB_HERO_DOWN_WALK1, RGB(255, 255, 255));
	animation_D.AddBitmap(IDB_HERO_DOWN_WALK2, RGB(255, 255, 255));
	animation_D.AddBitmap(IDB_HERO_DOWN_WALK3, RGB(255, 255, 255));
	animation_L.AddBitmap(IDB_HERO_LEFT_WALK0, RGB(255, 255, 255));
	animation_L.AddBitmap(IDB_HERO_LEFT_WALK1, RGB(255, 255, 255));
	animation_L.AddBitmap(IDB_HERO_LEFT_WALK2, RGB(255, 255, 255));
	animation_L.AddBitmap(IDB_HERO_LEFT_WALK3, RGB(255, 255, 255));
	animation_R.AddBitmap(IDB_HERO_RIGHT_WALK0, RGB(255, 255, 255));
	animation_R.AddBitmap(IDB_HERO_RIGHT_WALK1, RGB(255, 255, 255));
	animation_R.AddBitmap(IDB_HERO_RIGHT_WALK2, RGB(255, 255, 255));
	animation_R.AddBitmap(IDB_HERO_RIGHT_WALK3, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_HERO_ATTACK0, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_HERO_ATTACK1, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_HERO_ATTACK2, RGB(255, 255, 255));
	animation_attack.AddBitmap(IDB_HERO_ATTACK3, RGB(255, 255, 255));
	animation_guard.AddBitmap(IDB_HERO_GUARD, RGB(255, 255, 255));
	animation_guard.AddBitmap(IDB_HERO_GUARD, RGB(255, 255, 255));
	animation_guard.AddBitmap(IDB_HERO_GUARD, RGB(255, 255, 255));
	animation_guard.AddBitmap(IDB_HERO_GUARD, RGB(255, 255, 255));
	animation_guard.AddBitmap(IDB_HERO_GUARD, RGB(255, 255, 255));
	animation_guard.AddBitmap(IDB_HERO_GUARD, RGB(255, 255, 255));
	HP_UI.LoadBitmap(IDB_LEVEL_UI, RGB(255, 255, 255));
	Gold_UI.LoadBitmap(IDB_GOLD_UI, RGB(255, 255, 255));
	BossDoorFailed.LoadBitmapA(IDB_ITEM_MENU, RGB(255, 255, 255));
}

int Hero::GetX1()
{
	/* 回傳座標 */
	return x;
}

int Hero::GetY1()
{
	return y;
}

int Hero::GetX2()
{
	return x + animation_L.Width();
}

int Hero::GetY2()
{
	return y + animation_L.Height();
}

int Hero::GetSizeX()
{
	return GetX2() - GetX1();
}

int Hero::GetSizeY()
{
	return GetY2() - GetY1();
}

int Hero::GetMaxHp()
{
	return MaxHp;
}

int Hero::GetMaxMp()
{
	return MaxMp;
}

int Hero::GetHp()
{
	return _HP;
}

int Hero::GetMp()
{
	return _MP;
}

int Hero::GetLastPositionX()
{
	return lastPosition_x;
}

int Hero::GetLastPositionY()
{
	return lastPosition_y;
}

int Hero::GetAttackDamage()
{
	return AttackDamage;
}

int Hero::GetWeaponGrade()
{
	return weapon_grade;
}

int Hero::GetArmorGrade()
{
	return armor_grade;
}

int Hero::GetShieldGrade()
{
	return shield_grade;
}

int Hero::GetSkillDamage()
{
	int Damage;

	if (skills[skillId]->GetDamage() > 0)
		Damage = skills[skillId]->GetDamage() + (level.GetLv() * level.GetLv() + SkillDamage);
	else
		Damage = skills[skillId]->GetDamage();

	return Damage;
}

int Hero::GetCurrentBattleState()
{
	return currentBattleState;
}

int Hero::GetGold()
{
	return Gold;
}

int Hero::GetLevel()
{
	return level.GetLv();
}

int Hero::GetItemAmount(int id)
{
	return items[id]->GetAmount();
}

int Hero::GetSkillManaCost(int id)
{
	return skills[id]->GetManaCost();
}

int Hero::GetBlockDamage()
{
	return blockDamage;
}

int Hero::GetTreasureAmount()
{
	return treasure;
}

int Hero::GetFinallyChest()
{
	return finally_chest;
}

void Hero::SetXY(int nx, int ny)
{
	x = nx;
	y = ny;
}

void Hero::SetLastXY(int nx, int ny)
{
	lastPosition_x = nx;
	lastPosition_y = ny;
}

void Hero::SetHp(int HP)
{
	_HP = MaxHp > HP ? HP : MaxHp;
}

void Hero::SetMp(int MP)
{
	_MP = MP;
}

void Hero::SetGold(int gold)
{
	// 改變錢錢~
	this->Gold += gold;
}

void Hero::SetMovingDown(bool flag)
{
	isMovingDown = flag;
}

void Hero::SetMovingLeft(bool flag)
{
	isMovingLeft = flag;
}

void Hero::SetMovingRight(bool flag)
{
	isMovingRight = flag;
}

void Hero::SetMovingUp(bool flag)
{
	isMovingUp = flag;
}

void Hero::SetAllMovingToFalse()
{
	// 停止所有動作
	SetMovingLeft(false);
	SetMovingRight(false);
	SetMovingUp(false);
	SetMovingDown(false);
}

void Hero::SetMovingState(int flag)
{
	lastMovingState = flag;
}

void Hero::SetMoveDistance(int dst)
{
	moveDistance = dst;
}

void Hero::SetRun(bool flag)
{
	isRunning = flag;
}

void Hero::SetGuard(bool flag)
{
	isGuard = flag;
}

void Hero::SetXp(int xp)
{
	level.SetXp(level.GetXp() + xp);
	SetLevel();
}

void Hero::SetLevel()
{
	// 改變等級級~
	while (level.GetXp() >= level.GetRequireXp())
	{
		level.SetXp(level.GetXp() - level.GetRequireXp());
		level.SetRequireXp();
		level.SetLv(level.GetLv() + 1);
		LevelUp();
	}
}

void Hero::SetItemAmount(int id, int amount)
{
	items[id]->SetItemAmount(items[id]->GetAmount() + amount);
}

void Hero::SetWeaponGrade(int lv)
{
	weapon_grade += lv;
	AttackDamage += weapon_grade * 5;
	SkillDamage += weapon_grade * 6;
}

void Hero::SetArmorGrade(int lv)
{
	armor_grade += lv;
	MaxHp += armor_grade * 47;
	SetHp(MaxHp);
}

void Hero::SetShieldGrade(int lv)
{
	shield_grade += lv;
	blockDamage = shield_grade * 5;
}

void Hero::SetTreasureAmount(int treasure)
{
	this->treasure = treasure;
}

void Hero::SetFinallyBattleEnd(bool flag)
{
	readllyFight = flag;
}

void Hero::SetFinallyChest(int  i)
{
	finally_chest += i;
}

void Hero::OpenBossDoor()
{
	if (isInFrontOfBoss_door)
	{
		if (GetTreasureAmount() != 3)
		{
			BossDoorFailed.SetTopLeft(300, 230);
			BossDoorFailed.ShowBitmap();
			CDC *pDC = CDDraw::GetBackCDC();
			CFont f, *fp;
			f.CreatePointFont(300, "Microsoft JhengHei");
			fp = pDC->SelectObject(&f);
			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			pDC->TextOut(370, 320, "我還沒收集完");
			pDC->TextOut(370, 400, "所有的神器ㄋ");
			pDC->SelectObject(fp);
			CDDraw::ReleaseBackCDC();
		}
		else
			readllyFight = true;
	}
}

void Hero::LevelUp()
{
	// 等級提升
	MaxHp = MaxHp + 7;
	MaxMp = MaxMp + 5;
	SetHp(MaxHp);
	SetMp(MaxMp);
	AttackDamage += 2;
	SkillDamage += 3;
}

bool Hero::NextStepIsEmpty(GameMap *map, bool movingState, int x1, int y1, int x2, int y2)
{
	return movingState && map->IsEmpty(x1, y1) && map->IsEmpty(x2, y2);
}

bool Hero::HasMeetMonster(GameMap *map)
{
	// 遇到怪物
	srand((unsigned)time(NULL));
	int min = 1000;
	int max = 2000;
	int rd = rand() % (max - min + 1) + min;

	if (isMoving())
		moveDistance += 10;

	if (GetReadllyFight() && !*_isBattling)
		moveDistance += 200;

	return moveDistance > rd;
}

bool Hero::isMoving()
{
	return isMovingDown || isMovingLeft || isMovingRight || isMovingUp;
}


bool Hero::isGuarding()
{
	return isGuard;
}

bool Hero::IsCollisionNpc()
{
	// 碰撞NPC
	for (size_t i = 0; i < npc->size(); i++)
		if ((*npc)[i]->HasCollision(GetX1(), GetY1(), GetX2(), GetY2()))
			return true;

	return false;
}

bool Hero::IsCollisionChest()
{
	// 碰撞寶箱
	for (size_t i = 0; i < chest->size(); i++)
		if ((*chest)[i]->HasCollision(GetX1(), GetY1(), GetX2(), GetY2()))
			return true;

	return false;
}

bool Hero::HasCollision(int x1, int y1, int x2, int y2, GameMap *map)
{
	// 碰撞到任何物品
	int minX1 = x1;
	int minY1 = y1;
	int maxX1 = x2;
	int maxY1 = y2;
	int minX2;
	int minY2;
	int maxX2;
	int maxY2;

	if (IsCollisionNpc())
	{
		for (size_t i = 0; i < npc->size(); i++)
		{
			minX2 = (*npc)[i]->GetX1();
			minY2 = (*npc)[i]->GetY1();
			maxX2 = (*npc)[i]->GetX2();
			maxY2 = (*npc)[i]->GetY2();

			// 兩個物體面積重疊就會碰撞
			if (maxX1 > minX2 && maxX2 > minX1 &&
			        maxY1 > minY2 && maxY2 > minY1)
			{
				animation_D.Reset();
				animation_L.Reset();
				animation_R.Reset();
				animation_U.Reset();
				return true;
			}
		}
	}

	if (IsCollisionChest())
	{
		for (size_t i = 0; i < chest->size(); i++)
		{
			minX2 = (*chest)[i]->GetX1();
			minY2 = (*chest)[i]->GetY1();
			maxX2 = (*chest)[i]->GetX2();
			maxY2 = (*chest)[i]->GetY2();

			// 兩個物體面積重疊就會碰撞
			if (maxX1 > minX2 && maxX2 > minX1 &&
			        maxY1 > minY2 && maxY2 > minY1)
			{
				animation_D.Reset();
				animation_L.Reset();
				animation_R.Reset();
				animation_U.Reset();
				return true;
			}
		}
	}

	minX2 = map->GetBossDoorX();
	minY2 = map->GetBossDoorY();
	maxX2 = map->GetBossDoorX2();
	maxY2 = map->GetBossDoorY2();

	// 兩個物體面積重疊就會碰撞
	if (maxX1 > minX2 && maxX2 > minX1 &&
	        maxY1 > minY2 && maxY2 > minY1)
	{
		animation_D.Reset();
		animation_L.Reset();
		animation_R.Reset();
		animation_U.Reset();
		isInFrontOfBoss_door = true;
		return true;
	}
	else
		isInFrontOfBoss_door = false;

	return false;
}

bool Hero::IsRespone()
{
	// 選擇回覆中
	for (size_t i = 0; i < npc->size(); i++)
		if ((*npc)[i]->IsRespone())
			return true;

	return false;
}

bool Hero::GetReadllyFight()
{
	return readllyFight;
}

void Hero::OnMove(GameMap *map)
{
	Moving(map);
	Attacking();
	Guarding();
	Healing();
	Skilling();
}

void Hero::Moving(GameMap *map)
{
	// 移動
	// 判斷是不是在跑步再給移動距離
	int step;
	TRACE("%d %d\n", x, y);
	isRunning == true ? step = RUN_SIZE : step = STEP_SIZE;

	if (NextStepIsEmpty(map, isMovingLeft, x - STEP_SIZE - GetSizeX(), y, x - STEP_SIZE - GetSizeX(), y))
	{
		if (!HasCollision(x - step, y + 25, GetX2(), GetY2(), map))
		{
			lastPosition_x = x;
			x -= step;
			animation_L.OnMove();

			if (map->ScreenX(x) < 1024 / 2 - 50 && x > 580)
				// 判斷主角位置決定視角移動
				map->MoveScreenX(-step);
		}
	}

	if (NextStepIsEmpty(map, isMovingRight, x + STEP_SIZE, y, x + STEP_SIZE, y))
	{
		if (!HasCollision(x, y + 25, GetX2() + step, GetY2(), map))
		{
			lastPosition_x = x;
			x += step;
			animation_R.OnMove();

			if (map->ScreenX(x) > 1024 / 2 && x < 5475)
				// 判斷主角位置決定視角移動
				map->MoveScreenX(step);
		}
	}

	if (NextStepIsEmpty(map, isMovingUp, x, y - STEP_SIZE, x - GetSizeX(), y - STEP_SIZE))
	{
		if (!HasCollision(x, y - step + 25, GetX2(), GetY2(), map))
		{
			lastPosition_y = y;
			y -= step;
			animation_U.OnMove();

			if (map->ScreenY(y) < 768 / 2 - 50 && y > 440)
				// 判斷主角位置決定視角移動
				map->MoveScreenY(-step);
		}
	}

	if (NextStepIsEmpty(map, isMovingDown, x, y + STEP_SIZE + 25, x - GetSizeX(), y + STEP_SIZE + 25))
	{
		if (!HasCollision(x, y + 25, GetX2(), GetY2() + step, map))
		{
			lastPosition_y = y;
			y += step;
			animation_D.OnMove();

			if (map->ScreenY(y) > 768 / 2 && y < 1700)
				// 判斷主角位置決定視角移動
				map->MoveScreenY(step);
		}
	}
}

void Hero::Attacking()
{
	/* 這種動畫 */
	if (isAttack)
	{
		SetXY(-700 - 75, -400);
		animation_attack.OnMove();

		// 當攻擊動畫跑完就結束攻擊動作
		if (animation_attack.GetCurrentBitmapNumber() == 3)
		{
			SetXY(-1200, -400);
			isAttack = false;
			currentBattleState = 0;
		}
	}
}

void Hero::AttackMonster(Monster &monster)
{
	isAttack = true;
	currentBattleState = 1;
	CAudio::Instance()->Play(AUDIO_SWORD, false);

	if (monster.GetHp() > 0)
		animation_attack.Reset();

	if (monster.GetHp() - GetAttackDamage() > 0)
	{
		monster.SetHurtDamage(true);
		monster.SetHp(monster.GetHp() - GetAttackDamage());
	}
	else
		monster.SetHp(0);
}

void Hero::SkillAttackMonster(Monster &monster, int Id)
{
	//回復技能得傷害先設定成負，代表他是回復技能
	this->skillId = Id;

	if (skills[skillId]->GetManaCost() <= _MP)
	{
		currentBattleState = 4;
		isSkill = true;
		_MP -= skills[skillId]->GetManaCost();

		if (skills[skillId]->GetDamage() > 0)
		{
			int Damage = skills[skillId]->GetDamage() + (level.GetLv() * level.GetLv() + SkillDamage);

			if (monster.GetHp() - Damage > 0)
			{
				monster.SetHp(monster.GetHp() - Damage);
				monster.SetHurtDamage(true);
			}
			else
				monster.SetHp(0);
		}
		else
		{
			int Damage = (skills[skillId]->GetDamage()) - (level.GetLv() * level.GetLv() + SkillDamage);
			int hp = GetHp() + Damage * -1;
			hp = hp >= GetMaxHp() ? GetMaxHp() : hp;
			SetHp(hp);
		}
	}
}

void Hero::Guarding()
{
	if (isGuard)
	{
		animation_guard.OnMove();

		if (animation_guard.IsFinalBitmap())
			isGuard = false;
	}
}

void Hero::Healing()
{
	if (isHeal)
	{
		items[itemId]->OnMove();

		// 判斷觸發哪個道具
		if (items[itemId]->AnimationIsFinalBitmap())
		{
			isHeal = false;
			items[itemId]->SetItemAmount(items[itemId]->GetAmount() - 1);
			items[itemId]->AnimationReset();
			currentBattleState = 0;
		}
	}
}

void Hero::UseItem(int id)
{
	//輸入要使用的道具編號
	if (items[id]->GetCurrentBitmapNumber() == 0 && items[id]->GetAmount() > 0)
	{
		itemId = id;
		isHeal = true;
		currentBattleState = 3;
		items[itemId]->Use(this);
	}
}

void Hero::Skilling()
{
	if (isSkill)
	{
		skills[skillId]->OnMove();

		// 判斷觸發哪個技能
		if (skills[skillId]->AnimationIsFinalBitmap())
		{
			isSkill = false;
			skills[skillId]->AnimationReset();
			currentBattleState = 0;
		}
	}
}

void Hero::OnKeyDown(UNIT nChar)
{
	const char KEY_LEFT = 0x25;
	// keyboard左箭頭
	const char KEY_UP = 0x26;
	// keyboard上箭頭
	const char KEY_RIGHT = 0x27;
	// keyboard右箭頭
	const char KEY_DOWN = 0x28;
	// keyboard下箭頭
	const char KEY_Z = 0x5A;
	// keyboard Z
	const char KEY_X = 0x58;
	// keyboard X
	const char KEY_P = 0x50;
	const char KEY_ENTER = 0x0D;

	if (nChar == KEY_ENTER)
	{
		isPressEnter = true;
	}

	if (nChar == KEY_LEFT)
	{
		SetMovingLeft(true);
		SetMovingState(0);
	}

	if (nChar == KEY_RIGHT)
	{
		SetMovingRight(true);
		SetMovingState(1);
	}

	if (nChar == KEY_UP)
	{
		SetMovingUp(true);
		SetMovingState(2);
	}

	if (nChar == KEY_DOWN)
	{
		SetMovingDown(true);
		SetMovingState(3);
	}

	if (nChar == KEY_Z)
		SetRun(true);

	// 跑步
	if (nChar == KEY_X)
	{
		UseItem(0);
		// 使用Potion
		CAudio::Instance()->Play(AUDIO_SPELL, false);
	}

	if (nChar == KEY_P)
	{
		// 升級
		level.SetLv(level.GetLv() + 2);
		AttackDamage += level.GetLv() * 200;
		SkillDamage += AttackDamage;
		MaxHp += 7000;
		SetHp(MaxHp);
		RUN_SIZE = 15;
		MaxMp += 7;
		SetMp(MaxMp);
		SetGold(5000);
		treasure = 3;
		SetXp(9);
	}
}

void Hero::OnKeyUp(UNIT nChar)
{
	const char KEY_LEFT = 0x25;
	// keyboard左箭頭
	const char KEY_UP = 0x26;
	// keyboard上箭頭
	const char KEY_RIGHT = 0x27;
	// keyboard右箭頭
	const char KEY_DOWN = 0x28;
	// keyboard下箭頭
	const char KEY_Z = 0x5A;
	// keyboard Z
	const char KEY_ENTER = 0x0D;

	if (nChar == KEY_ENTER)
	{
		isPressEnter = false;
	}

	if (nChar == KEY_LEFT)
		SetMovingLeft(false);

	if (nChar == KEY_RIGHT)
		SetMovingRight(false);

	if (nChar == KEY_UP)
		SetMovingUp(false);

	if (nChar == KEY_DOWN)
		SetMovingDown(false);

	if (nChar == KEY_Z)
		SetRun(false);
}

void Hero::OnShow(GameMap *map, AdjustableCInteger *printNum, CInteger *printNum2)
{
	AnimationMove(map);
	AnimationAttack(map);
	AnimationGuard(map);
	AnimationHeal(map);
	OpenBossDoor();
}

void Hero::ShowUI(GameMap *map, AdjustableCInteger *printNum)
{
	if (!*_isBattling)
	{
		ShowHeroUI(map, printNum);
		ShowGoldUI(map, printNum);
	}
}

void Hero::ShowHeroUI(GameMap *map, AdjustableCInteger *printNum)
{
	HP_UI.SetTopLeft(map->ScreenX(map->GetScreenX() + 25), map->ScreenY(map->GetScreenY() + 10));
	HP_UI.ShowBitmap();
	ShowHp(map->ScreenX(map->GetScreenX() + 125), map->ScreenY(map->GetScreenY() + 40), GetHp());
	ShowMp(map->ScreenX(map->GetScreenX() + 125), map->ScreenY(map->GetScreenY() + 65 - 25 / 8 ), GetMp());
	ShowXp(map->ScreenX(map->GetScreenX() + 120), map->ScreenY(map->GetScreenY() + 165), level.GetXp(), level.GetRequireXp());
	PrintNumber(map, printNum, GetLevel(), map->ScreenX(map->GetScreenX() + 35 + 3), map->ScreenY(map->GetScreenY() + 135));
}

void Hero::ShowGoldUI(GameMap *map, AdjustableCInteger *printNum)
{
	Gold_UI.SetTopLeft(map->ScreenX(map->GetScreenX() + 25), map->ScreenY(map->GetScreenY() + 650));
	Gold_UI.ShowBitmap();
	PrintNumber(map, printNum, GetGold(), map->ScreenX(map->GetScreenX() + 160), map->ScreenY(map->GetScreenY() + 685));
}

void Hero::PrintNumber(GameMap *map, AdjustableCInteger *printNum, int number, int nx, int ny)
{
	printNum->SetInteger(number);
	printNum->SetTopLeft(nx, ny);
	printNum->ShowBitmap();
}

void Hero::AnimationMove(GameMap *map)
{
	if (isMovingRight)
	{
		animation_R.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_R.OnShow();
	}
	else if (isMovingLeft)
	{
		animation_L.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_L.OnShow();
	}
	else if (isMovingUp)
	{
		animation_U.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_U.OnShow();
	}
	else if (isMovingDown)
	{
		animation_D.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_D.OnShow();
	}
	else
		doStandingAnimation(map);
}

void Hero::doStandingAnimation(GameMap *map)
{
	// 站著
	switch (lastMovingState)
	{
		case 0: // 左
			animation_L.Reset();
			animation_L.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
			animation_L.OnShow();
			break;

		case 1: // 右
			animation_R.Reset();
			animation_R.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
			animation_R.OnShow();
			break;

		case 2: // 上
			animation_U.Reset();
			animation_U.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
			animation_U.OnShow();
			break;

		case 3: // 下
			animation_D.Reset();
			animation_D.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
			animation_D.OnShow();
			break;
	}
}

void Hero::AnimationAttack(GameMap *map)  					/* 顯示各種動畫 */
{
	if (isAttack && *_isBattling)
	{
		animation_attack.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_attack.OnShow();
	}
}

void Hero::AnimationGuard(GameMap *map)
{
	if (isGuard)
	{
		animation_guard.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_guard.OnShow();
	}
}

void Hero::AnimationGuardReset()
{
	animation_guard.Reset();
}

void Hero::AnimationHeal(GameMap *map)
{
	if (isHeal && items[itemId]->GetAmount() > 0)
	{
		items[itemId]->OnShowEffect(map->ScreenX(x - 105), map->ScreenY(y - 140));
	}
}

void Hero::AnimationSkill(GameMap *map)
{
	if (isSkill && skills[skillId]->GetManaCost() <= _MP  )
	{
		skills[skillId]->OnShowEffect(map);
	}
}

void Hero::ShowHp(int x1, int y1, int percent)
{
	percent = percent <= 0 ? 0 : percent;
	int bar_width = 300;
	int bar_height = 25;
	const int x2 = x1 + bar_width;
	const int y2 = y1 + bar_height;
	const int pen_width = bar_height / 8;
	const int progress_x1 = x1 + pen_width;
	const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / MaxHp;
	const int progress_x2_end = x2 - pen_width;
	const int progress_y1 = y1 + pen_width;
	const int progress_y2 = y2 - pen_width;
	CDC *pDC = CDDraw::GetBackCDC();
	CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));
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
	pDC->SelectObject(pb);
	CDDraw::ReleaseBackCDC();
}

void Hero::ShowMp(int x1, int y1, int percent)
{
	percent = percent <= 0 ? 0 : percent;
	int bar_width = 240;
	int bar_height = 20;
	const int x2 = x1 + bar_width;
	const int y2 = y1 + bar_height;
	const int pen_width = bar_height / 8;
	const int progress_x1 = x1 + pen_width;
	const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / MaxMp;
	const int progress_x2_end = x2 - pen_width;
	const int progress_y1 = y1 + pen_width;
	const int progress_y2 = y2 - pen_width;
	CDC *pDC = CDDraw::GetBackCDC();
	CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));
	pp = pDC->SelectObject(&p);
	CBrush *pb, b(RGB(0, 0, 0));
	pb = pDC->SelectObject(&b);
	pDC->Rectangle(x1, y1, x2, y2);
	CBrush b1(RGB(192, 192, 192));
	pDC->SelectObject(&b1);
	pDC->Rectangle(progress_x1, progress_y1, progress_x2_end, progress_y2);
	CBrush b2(RGB(93, 188, 220));
	pDC->SelectObject(&b2);
	pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
	pDC->SelectObject(pp);
	pDC->SelectObject(pb);
	CDDraw::ReleaseBackCDC();
}

void Hero::ShowXp(int x1, int y1, int percent, int maxPercent)
{
	int bar_width = 195;
	int bar_height = 10;
	const int x2 = x1 + bar_width;
	const int y2 = y1 + bar_height;
	const int pen_width = bar_height / 8;
	const int progress_x1 = x1 + pen_width;
	const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / maxPercent;
	const int progress_x2_end = x2 - pen_width;
	const int progress_y1 = y1 + pen_width;
	const int progress_y2 = y2 - pen_width;
	CDC *pDC = CDDraw::GetBackCDC();
	CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));
	pp = pDC->SelectObject(&p);
	CBrush *pb, b(RGB(96, 48, 56));
	pb = pDC->SelectObject(&b);
	pDC->Rectangle(x1, y1, x2, y2);
	CBrush b1(RGB(96, 48, 56));
	pDC->SelectObject(&b1);
	pDC->Rectangle(progress_x1, progress_y1, progress_x2_end, progress_y2);
	CBrush b2(RGB(100, 169, 240));
	pDC->SelectObject(&b2);
	pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
	pDC->SelectObject(pp);
	pDC->SelectObject(pb);
	CDDraw::ReleaseBackCDC();
}

void Hero::ShowPotion(GameMap *map, AdjustableCInteger *printNum)
{
	if (!*_isBattling && !IsRespone())
	{
		items[0]->OnShowIcon(map->ScreenX(map->GetScreenX() + 850), map->ScreenY(map->GetScreenY() + 610));
		printNum->SetInteger(items[0]->GetAmount());
		printNum->SetTopLeft(map->ScreenX(map->GetScreenX() + 920), map->ScreenY(map->GetScreenY() + 640));
		printNum->ShowBitmap();
	}
}
}