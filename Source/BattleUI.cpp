#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Monster.h"
#include "Hero.h"
#include "GameMap.h"
#include "BattleUI.h"
#include "mygame.h"
#define NUM_WIDTH 20
#define NUM_HEIGHT 20
#define BAR_WIDTH  300
#define BAR_HEIGHT 20
#define HERO_X -1200
#define HERO_Y -400
#define MON_X -700
#define MON_Y -400

namespace game_framework
{

BattleUI::BattleUI()
{
	// Initialize
}

void BattleUI::Initialize(GameMap *map, Hero *hero, Monster *monster, bool *isBattling, bool *playWalkTheme)
{
	menu_x = -1375;
	menu_y = -250;
	battleBack_x = -1430;
	battleBack_y = -730;
	attack_x = skill_x = -1250;
	guard_x = attack_x + 250;
	escape_x = guard_x + 250;
	attack_y = guard_y = escape_y = -194;
	skill_y = attack_y + 100;
	item_x = guard_x;
	item_y = guard_y + 100;
	cursor_x = -1300;
	cursor_y = -180;
	itemMenu_x = -850;
	itemMenu_y = -300;
	skillMenu_x = -1050;
	skillMenu_y = -300;
	menu_selected_x = menu_selected_y = 0;
	item_index = 0;						// 物品索引
	total_item = 3;						// 最大物品數量
	skill_index = 0;					// 技能索引
	total_skill = 4;					// 最大技能數量
	item_potion_x = itemMenu_x + 100;
	item_potion_y = itemMenu_y + 50;
	item_ether_x = itemMenu_x + 100;
	item_ether_y = itemMenu_y + 100;
	skill_lightning_x = skillMenu_x + 100;
	skill_lightning_y = skillMenu_y + 50;
	skill_heal_x = skillMenu_x + 100;
	skill_heal_y = skillMenu_y + 117;
	heroLevel = hero->GetLevel();
	_isBattling = isBattling;
	this->map = map;
	this->hero = hero;
	this->monster = monster;
	*_isBattling = true;				// 進入戰鬥
	hero->SetAllMovingToFalse();
	hero->SetRun(false);
	hero->SetMovingState(1);			// 主角方向向右
	map->SetBattleScreenXY();
	hero->SetXY(-1200, -400);
	hero->SetMoveDistance(0);
	countTime = 0;
	delay = false;
	buttonIsPressed = false;
	itemMenuIsOpen = false;
	skillMenuIsOpen = false;
	enterFoolproof = true;
	finishHasOpen = false;
	escapefailedIsOpen = false;
	end = false;
	this->playWalkTheme = playWalkTheme;
}

void BattleUI::LoadBitmap()
{
	menuUI.LoadBitmap(IDB_BATTLE_UI, RGB(255, 255, 255));
	BattleBackground.LoadBitmap(IDB_BATTLE_BACK);
	FinallyBattleBackground.LoadBitmap(IDB_BATTLE_BOSS_BACKGROUND);
	AttackBtn.LoadBitmap(IDB_ATTACK_BTN, RGB(255, 255, 255));
	SkillBtn.LoadBitmap(IDB_SKILL_BTN, RGB(255, 255, 255));
	ItemBtn.LoadBitmap(IDB_ITEM_BTN, RGB(255, 255, 255));
	GuardBtn.LoadBitmap(IDB_GUARD_BTN, RGB(255, 255, 255));
	EscapeBtn.LoadBitmap(IDB_ESCAPE_BTN, RGB(255, 255, 255));
	Cursor.LoadBitmap(IDB_CURSOR, RGB(255, 255, 255));
	ItemMenu.LoadBitmap(IDB_ITEM_MENU, RGB(255, 255, 255));
	SkillMenu.LoadBitmap(IDB_ITEM_MENU, RGB(255, 255, 255));
	ItemPotion.LoadBitmap(IDB_ITEM_POTION, RGB(255, 255, 255));
	ItemEther.LoadBitmap(IDB_ETHER, RGB(255, 255, 255));
	SkillHeal.LoadBitmap(IDB_SKILL_HEAL, RGB(255, 255, 255));
	SkillLightning.LoadBitmap(IDB_SKILL_LIGHTNING, RGB(255, 255, 255));
	Back.LoadBitmap(IDB_BACK, RGB(255, 255, 255));
	BattleFinishBackground.LoadBitmap(IDB_BATTLE_FINISH, RGB(255, 255, 255));
	heroIcon.LoadBitmap(IDB_HERO_DOWN_WALK0, RGB(255, 255, 255));
	EscapeFailed.LoadBitmapA(IDB_ESCAPEFAILED, RGB(255, 255, 255));
	SkillThunder.LoadBitmap(IDB_THUNDER, RGB(255, 255, 255));
}

void BattleUI::Attack()
{
	// 攻擊
	hero->AttackMonster(*monster);
	// 主角攻擊怪物
	monster->RandomDecision(*hero);
	// 怪物行動
	delay = true;
}

void BattleUI::Skill(UNIT nChar)
{
	const int UP_ARROW_KEY = 0x26;
	const int DOWN_ARROW_KEY = 0x28;

	if (skillMenuIsOpen)
	{
		// 技能選單控制
		if (nChar == UP_ARROW_KEY)
		{
			if (skill_index > 0)
				skill_index--;
			else
				skill_index = total_skill - 1;
		}

		if (nChar == DOWN_ARROW_KEY)
		{
			if (skill_index < total_skill - 1)
				skill_index++;
			else
				skill_index = 0;
		}

		if (!enterFoolproof)
			// 防呆打開
			SkillPress(nChar);

		TRACE("skillMenuIsOpen = %d \n", skill_index);
		enterFoolproof = false;
	}
}

void BattleUI::SkillPress(UNIT nChar)
{
	// 技能選擇
	const int ENTER_KEY = 0x0D;

	if (nChar == ENTER_KEY)
	{
		if (skill_index == 0)
		{
			if (hero->GetSkillManaCost(skill_index) <= hero->GetMp())
				CAudio::Instance()->Play(AUDIO_LIGHTNING, false);

			hero->SkillAttackMonster(*monster, skill_index);
			monster->RandomDecision(*hero);
			skillMenuIsOpen = false;
			// 選擇完技能後關閉技能小窗
			delay = true;
		}

		if (skill_index == 1)
		{
			if (hero->GetSkillManaCost(skill_index) <= hero->GetMp())
				CAudio::Instance()->Play(AUDIO_SPELL, false);

			hero->SkillAttackMonster(*monster, skill_index);
			monster->SetMonsterDelay(true);
			monster->RandomDecision(*hero);
			skillMenuIsOpen = false;
			delay = true;
		}

		if (skill_index == 2)
		{
			if (hero->GetSkillManaCost(skill_index) <= hero->GetMp())
				CAudio::Instance()->Play(AUDIO_LIGHTNING, false);

			hero->SkillAttackMonster(*monster, skill_index);
			monster->RandomDecision(*hero);
			skillMenuIsOpen = false;
			delay = true;
		}

		if (skill_index == total_skill - 1)
		{
			// 返回鍵
			skillMenuIsOpen = false;
			buttonIsPressed = false;
		}
	}
}

void BattleUI::Item(UNIT nChar)
{
	// 物品
	const int UP_ARROW_KEY = 0x26;
	const int DOWN_ARROW_KEY = 0x28;

	if (itemMenuIsOpen)
	{
		// 物品選單控制
		if (nChar == UP_ARROW_KEY)
			item_index = item_index > 0 ? --item_index : total_item - 1;

		if (nChar == DOWN_ARROW_KEY)
			item_index = item_index < (total_item - 1) ? ++item_index : 0;

		if (!enterFoolproof)
			// 防呆打開
			ItemPress(nChar);

		enterFoolproof = false;
	}
}

void BattleUI::ItemPress(UNIT nChar)
{
	// 物品選擇
	const int ENTER_KEY = 0x0D;

	if (nChar == ENTER_KEY)
	{
		if (item_index == 0)
		{
			if (hero->GetItemAmount(item_index) > 0)
				CAudio::Instance()->Play(AUDIO_SPELL, false);

			hero->UseItem(item_index);
			monster->SetMonsterDelay(true);
			monster->RandomDecision(*hero);
			itemMenuIsOpen = false;
			// 物品選擇完關閉物品小窗
			delay = true;
		}

		if (item_index == 1)
		{
			if (hero->GetItemAmount(item_index) > 0)
				CAudio::Instance()->Play(AUDIO_SPELL, false);

			hero->UseItem(item_index);
			monster->SetMonsterDelay(true);
			monster->RandomDecision(*hero);
			itemMenuIsOpen = false;
			delay = true;
		}

		if (item_index == total_item - 1)
		{
			// 返回鍵
			itemMenuIsOpen = false;
			buttonIsPressed = false;
		}
	}
}

void BattleUI::Guard()
{
	// 防禦
	hero->SetGuard(true);
	hero->AnimationGuardReset();
	monster->SetMonsterDelay(true);
	monster->RandomDecision(*hero);
	delay = true;
}

void BattleUI::Escape()
{
	// 逃跑，是有可能失敗的
	srand((unsigned)time(NULL));
	int max = 10;
	int rd = rand() % max + 1;

	if (rd <= 3)
	{
		hero->SetXY(hero->GetLastPositionX(), hero->GetLastPositionY());
		map->SetScreenXY(map->GetLastScreenX(), map->GetLastScreenY());
		*_isBattling = false;
		*playWalkTheme = true;
		buttonIsPressed = false;
	}
	else
	{
		escapefailedIsOpen = true;
		monster->SetMonsterDelay(true);
		monster->RandomDecision(*hero);
		delay = true;
	}
}

void BattleUI::StopAMoment()
{
	// delay 時間
	if (countTime == 25 && escapefailedIsOpen)
	{
		escapefailedIsOpen = false;
		countTime = 0;
	}

	if (countTime == 50)
	{
		countTime = 0;
		delay = false;
		buttonIsPressed = false;
	}
	else
		countTime++;
}

void BattleUI::GainGold()
{
	// 獲得金錢
	hero->SetGold(monster->GetGold());
}

void BattleUI::GainXp()
{
	// 獲得經驗值
	if (!finishHasOpen)
		hero->SetXp(monster->GetXp());
}

void BattleUI::OnkeyDown(UNIT nChar)
{
	MenuControl(nChar);
	MenuPress(nChar);
	Item(nChar);
	Skill(nChar);
	BackToMap(nChar);
}

void BattleUI::MenuControl(UNIT nChar)
{
	// 選單介面控制
	const int LEFT_ARROW_KEY = 0x25;
	const int UP_ARROW_KEY = 0x26;
	const int RIGHT_ARROW_KEY = 0x27;
	const int DOWN_ARROW_KEY = 0x28;

	if (!itemMenuIsOpen && !skillMenuIsOpen)
	{
		if (nChar == LEFT_ARROW_KEY)
		{
			menu_selected_y -= 1;

			if (menu_selected_y < 0)
			{
				if (menu_selected_x == 0)
					menu_selected_y = 2;
				else
					menu_selected_y = 1;
			}
		}

		if (nChar == UP_ARROW_KEY)
		{
			menu_selected_x -= 1;

			if (menu_selected_x < 0)
			{
				if (menu_selected_y == 2)
					menu_selected_x = 0;
				else
					menu_selected_x = 1;
			}
		}

		if (nChar == RIGHT_ARROW_KEY)
		{
			menu_selected_y += 1;

			if (menu_selected_x == 0 && menu_selected_y > 2 || menu_selected_x == 1 && menu_selected_y > 1)
				menu_selected_y = 0;
		}

		if (nChar == DOWN_ARROW_KEY)
		{
			menu_selected_x += 1;

			if (menu_selected_y == 0 && menu_selected_x > 1 || menu_selected_y == 1 && menu_selected_x > 1 || menu_selected_y == 2 && menu_selected_x > 0)
				menu_selected_x = 0;
		}
	}
}

void BattleUI::MenuPress(UNIT nChar)
{
	// 選單選擇
	const int ENTER_KEY = 0x0D;

	if (nChar == ENTER_KEY && !buttonIsPressed && hero->GetCurrentBattleState() == 0 && monster->GetCurrentBattleState() == 0 && !finishHasOpen)
	{
		buttonIsPressed = true;

		if (menu_selected_x == 0 && menu_selected_y == 0)
			// Attack
			Attack();
		else if (menu_selected_x == 0 && menu_selected_y == 1)
			// Guard
			Guard();
		else if (menu_selected_x == 0 && menu_selected_y == 2)
			// Escape
			Escape();
		else if (menu_selected_x == 1 && menu_selected_y == 0)
		{
			// Skill
			skillMenuIsOpen = true;
			enterFoolproof = true;
			skill_index = 0;
		}
		else if (menu_selected_x == 1 && menu_selected_y == 1)
		{
			// Item
			itemMenuIsOpen = true;
			enterFoolproof = true;
			item_index = 0;
		}
	}
}

void BattleUI::OnShow(AdjustableCInteger *NumberUI, CInteger *printNum)
{
	// 戰鬥背景
	ShowBackground();
	// 顯示選單
	ShowMenu();
	// 顯示物品選單
	ShowItemMenu(printNum);
	// 顯示技能選單
	ShowSkillMenu(printNum);
	// 主角血條與魔力
	ShowHeroLifeManaBar(printNum);
	// 怪物血條
	ShowMonsterLifeBar(printNum);
	/* 選取小手 */
	ShowCursor();
	//	結算畫面
	ShowBattleFinishBackground();
	//	結算畫面的英雄圖案
	ShowHeroIcon();

	if (delay)
		StopAMoment();
}

void BattleUI::ShowBackground()
{
	// 顯示背景
	if (hero->GetReadllyFight())
	{
		FinallyBattleBackground.SetTopLeft(map->ScreenX(battleBack_x), map->ScreenY(battleBack_y));
		FinallyBattleBackground.ShowBitmap();
	}
	else
	{
		BattleBackground.SetTopLeft(map->ScreenX(battleBack_x), map->ScreenY(battleBack_y));
		BattleBackground.ShowBitmap();
	}
}

void BattleUI::ShowMenu()
{
	// 顯示選單
	menuUI.SetTopLeft(map->ScreenX(menu_x), map->ScreenY(menu_y));
	AttackBtn.SetTopLeft(map->ScreenX(attack_x), map->ScreenY(attack_y));
	SkillBtn.SetTopLeft(map->ScreenX(skill_x), map->ScreenY(skill_y));
	ItemBtn.SetTopLeft(map->ScreenX(item_x), map->ScreenY(item_y));
	GuardBtn.SetTopLeft(map->ScreenX(guard_x), map->ScreenY(guard_y));
	EscapeBtn.SetTopLeft(map->ScreenX(escape_x), map->ScreenY(escape_y));
	menuUI.ShowBitmap();
	AttackBtn.ShowBitmap();
	SkillBtn.ShowBitmap();
	ItemBtn.ShowBitmap();
	GuardBtn.ShowBitmap();
	EscapeBtn.ShowBitmap();
}

void BattleUI::ShowItemMenu(CInteger *printNum)
{
	// 顯示物品小窗
	if (itemMenuIsOpen)
	{
		ItemMenu.SetTopLeft(map->ScreenX(itemMenu_x), map->ScreenY(itemMenu_y));
		ItemPotion.SetTopLeft(map->ScreenX(item_potion_x), map->ScreenY(item_potion_y));
		ItemEther.SetTopLeft(map->ScreenX(item_ether_x), map->ScreenY(item_ether_y));
		Back.SetTopLeft(map->ScreenX(itemMenu_x + 100), map->ScreenY(itemMenu_y + 250));
		ItemMenu.ShowBitmap();
		ItemPotion.ShowBitmap();
		ItemEther.ShowBitmap();
		Back.ShowBitmap();
		// 物品1數量
		printNum->SetInteger(hero->GetItemAmount(0));
		printNum->SetTopLeft(map->ScreenX(itemMenu_x + 310), map->ScreenY(itemMenu_y + 50));
		printNum->ShowBitmap();
		// 物品2數量
		printNum->SetInteger(hero->GetItemAmount(1));
		printNum->SetTopLeft(map->ScreenX(itemMenu_x + 310), map->ScreenY(itemMenu_y + 100));
		printNum->ShowBitmap();
	}
}

void BattleUI::ShowSkillMenu(CInteger *printNum)
{
	// 顯示技能小窗
	if (skillMenuIsOpen)
	{
		SkillMenu.SetTopLeft(map->ScreenX(skillMenu_x), map->ScreenY(skillMenu_y));
		SkillLightning.SetTopLeft(map->ScreenX(skill_lightning_x), map->ScreenY(skill_lightning_y));
		SkillHeal.SetTopLeft(map->ScreenX(skill_heal_x), map->ScreenY(skill_heal_y));
		SkillThunder.SetTopLeft(map->ScreenX(skillMenu_x + 100), map->ScreenY(skillMenu_y + 117 + 67));
		Back.SetTopLeft(map->ScreenX(skillMenu_x + 100), map->ScreenY(skillMenu_y + 250));
		SkillMenu.ShowBitmap();
		SkillLightning.ShowBitmap();
		SkillThunder.ShowBitmap();
		SkillHeal.ShowBitmap();
		Back.ShowBitmap();
		// 耗魔量數字
		printNum->SetInteger(hero->GetSkillManaCost(0));
		printNum->SetTopLeft(map->ScreenX(skillMenu_x + 310), map->ScreenY(skillMenu_y + 50));
		printNum->ShowBitmap();
		printNum->SetInteger(hero->GetSkillManaCost(1));
		printNum->SetTopLeft(map->ScreenX(skillMenu_x + 310), map->ScreenY(skillMenu_y + 117));
		printNum->ShowBitmap();
		printNum->SetInteger(hero->GetSkillManaCost(2));
		printNum->SetTopLeft(map->ScreenX(skillMenu_x + 310), map->ScreenY(skillMenu_y + 184));
		printNum->ShowBitmap();
	}
}

void BattleUI::ShowHeroLifeManaBar(CInteger *printNum)
{
	// 顯示英雄數值
	/////////////////////////////////////////////////////////////////////////////
	// 主角血條
	/////////////////////////////////////////////////////////////////////////////
	hero->ShowHp(map->ScreenX(-1400), map->ScreenY(-695), hero->GetHp());
	printNum->SetInteger(hero->GetHp());
	printNum->SetTopLeft(map->ScreenX(-1400 + BAR_WIDTH - NUM_WIDTH * 3), map->ScreenY(-700 - NUM_HEIGHT));
	printNum->ShowBitmap();
	/////////////////////////////////////////////////////////////////////////////
	// 主角魔力
	/////////////////////////////////////////////////////////////////////////////
	hero->ShowMp(map->ScreenX(-1400), map->ScreenY(-665 + NUM_HEIGHT ), hero->GetMp());
	printNum->SetInteger(hero->GetMp());
	printNum->SetTopLeft(map->ScreenX(-1400 + BAR_WIDTH - NUM_WIDTH * 3 - 60), map->ScreenY(-670));
	printNum->ShowBitmap();
}

void BattleUI::ShowMonsterLifeBar(CInteger *printNum)
{
	// 顯示怪物數值
	monster->ShowHp(map->ScreenX(-775), map->ScreenY(-695), monster->GetHp());
	printNum->SetInteger(monster->GetHp());
	printNum->SetTopLeft(map->ScreenX(-775 + BAR_WIDTH - NUM_WIDTH * 3), map->ScreenY(-700 - NUM_HEIGHT));
	printNum->ShowBitmap();
}

void BattleUI::ShowCursor()
{
	//顯示鼠標
	if (itemMenuIsOpen)
		ShowItemCursor();
	// 打開item裡的小手
	else if (skillMenuIsOpen)
		ShowSkillCursor();
	// 打開skill裡的小手
	else if (!finishHasOpen)
		ShowMenuCursor();

	// menu裡的小手
	Cursor.SetTopLeft(map->ScreenX(cursor_x), map->ScreenY(cursor_y));
	Cursor.ShowBitmap();
}

void BattleUI::ShowMenuCursor()
{
	if (menu_selected_x == 0 && menu_selected_y == 0)
	{
		// Attack
		cursor_x = attack_x - 50;
		cursor_y = attack_y + 14;
	}
	else if (menu_selected_x == 0 && menu_selected_y == 1)
	{
		// Guard
		cursor_x = guard_x - 50;
		cursor_y = guard_y + 14;
	}
	else if (menu_selected_x == 0 && menu_selected_y == 2)
	{
		// Escape
		cursor_x = escape_x - 50;
		cursor_y = escape_y + 14;
	}
	else if (menu_selected_x == 1 && menu_selected_y == 0)
	{
		// Skill
		cursor_x = skill_x - 50;
		cursor_y = skill_y + 14;
	}
	else if (menu_selected_x == 1 && menu_selected_y == 1)
	{
		// Item
		cursor_x = item_x - 50;
		cursor_y = item_y + 14;
	}
}

void BattleUI::ShowItemCursor()
{
	// 顯示物品小窗的鼠標
	if (item_index == 0)
	{
		cursor_x = itemMenu_x + 50;
		cursor_y = itemMenu_y + 50;
	}
	else if (item_index == 1)
	{
		cursor_x = itemMenu_x + 50;
		cursor_y = itemMenu_y + 100;
	}
	/*else if (item_index == 2) {
		cursor_x = itemMenu_x + 50;
		cursor_y = itemMenu_y + 150;
	}
	else if (item_index == 3) {
		cursor_x = itemMenu_x + 50;
		cursor_y = itemMenu_y + 200;
	}*/
	else if (item_index == 2)
	{
		cursor_x = itemMenu_x + 50;
		cursor_y = itemMenu_y + 250;
	}
}

void BattleUI::ShowSkillCursor()
{
	// 顯示技能小窗得鼠標
	if (skill_index == 0)
	{
		cursor_x = skillMenu_x + 50;
		cursor_y = skillMenu_y + 50;
	}
	else if (skill_index == 1)
	{
		cursor_x = skillMenu_x + 50;
		cursor_y = skillMenu_y + 117;
	}
	else if (skill_index == 2)
	{
		cursor_x = skillMenu_x + 50;
		cursor_y = skillMenu_y + 183;
	}
	else if (skill_index == 3)
	{
		cursor_x = skillMenu_x + 50;
		cursor_y = skillMenu_y + 250;
	}
}

void BattleUI::ShowAttackDamage(AdjustableCInteger *printNum)
{
	// 顯示攻擊傷害數值
	if (hero->GetCurrentBattleState() == 1 || hero->GetCurrentBattleState() == 4 && hero->GetSkillDamage() > 0)  	// 攻擊動畫進行到揮刀的瞬間
	{
		hero->GetCurrentBattleState() == 1 ?
		printNum->SetInteger(hero->GetAttackDamage()) : printNum->SetInteger(hero->GetSkillDamage());
		printNum->SetTopLeft(map->ScreenX(MON_X - 15), map->ScreenY(MON_Y - 100));
		printNum->ShowBitmap();
	}
}

void BattleUI::ShowBattleFinishBackground()
{
	//印出字需要用的東西，她不可以共用所以要印出不同大小的字要創另一個
	if (monster->IsDead() && hero->GetCurrentBattleState() == 0)
	{
		CAudio::Instance()->Stop(AUDIO_BATTLE);
		CAudio::Instance()->Stop(AUDIO_BEHEMOTH_THEME);
		hero->SetXY(hero->GetLastPositionX(), hero->GetLastPositionY());
		BattleFinishBackground.SetTopLeft(map->ScreenX(battleBack_x + 250), map->ScreenY(battleBack_y + 180));
		BattleFinishBackground.ShowBitmap();
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f, *fp;
		f.CreatePointFont(400, "Microsoft JhengHei");
		fp = pDC->SelectObject(&f);
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		char str[80];
		sprintf(str, "Lv %d  ->  ", heroLevel);
		pDC->TextOut(280, 210, str);
		GainXp();
		sprintf(str, " Lv %d ", hero->GetLevel());
		pDC->TextOut(550, 210, str);
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
		CDC *pDC2 = CDDraw::GetBackCDC();
		CFont f2, *fp2;
		f2.CreatePointFont(200, "Microsoft JhengHei");
		fp2 = pDC2->SelectObject(&f2);
		pDC2->SetBkColor(RGB(0, 0, 0));
		pDC2->SetTextColor(RGB(0, 0, 0));
		pDC2->SetBkMode(TRANSPARENT);
		sprintf(str, "獲得 %d 經驗", monster->GetXp());
		pDC2->TextOut(420, 450, str);
		sprintf(str, "獲得 %d 金錢", monster->GetGold());
		pDC2->TextOut(420, 500, str);
		pDC2->SelectObject(fp2);
		CDDraw::ReleaseBackCDC();

		if (!finishHasOpen && *_isBattling)
			CAudio::Instance()->Play(AUDIO_VICTORY_THEME, false);

		finishHasOpen = true;
	}
}

void BattleUI::ShowHeroIcon()
// 顯示主角圖片，結算畫面用
{
	if (finishHasOpen)
	{
		heroIcon.SetTopLeft(map->ScreenX(-950), map->ScreenY(-400));
		heroIcon.ShowBitmap();
	}
}

void BattleUI::ShowEscapefailed()
{
	if (escapefailedIsOpen)
	{
		EscapeFailed.SetTopLeft(map->ScreenX(battleBack_x + 300), map->ScreenY(battleBack_y + 180));
		EscapeFailed.ShowBitmap();
	}
}

void BattleUI::BackToMap(UNIT nChar)
{
	// 傳送回地圖
	const int ENTER_KEY = 0x0D;

	if (nChar == ENTER_KEY && finishHasOpen)
	{
		CAudio::Instance()->Stop(AUDIO_VICTORY_THEME);
		map->SetScreenXY(map->GetLastScreenX(), map->GetLastScreenY());
		hero->SetXY(hero->GetLastPositionX(), hero->GetLastPositionY());
		GainGold();
		*playWalkTheme = true;

		if (hero->GetReadllyFight())
		{
			//是否為最終決戰
			end = true;
		}

		*_isBattling = false;
	}
}
bool BattleUI::End()
{
	return end;
}
}