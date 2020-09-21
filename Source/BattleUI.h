#ifndef BATTLEUI_H
#define BATTLEUI_H
#include <vector>
namespace game_framework
{
typedef unsigned int UNIT;

class BattleUI
{
public:
	BattleUI();
	void Initialize(GameMap *map, Hero *hero, Monster *monster, bool *, bool *);
	void LoadBitmap();
	void Attack();											// 主角攻擊處理過場
	void Skill(UNIT);										// 主角技能處理過場
	void SkillPress(UNIT);									// 技能選擇
	void Item(UNIT);										// 主角使用道具處理過場
	void ItemPress(UNIT);									// 物品選擇
	void Guard();											// 主角防禦處理過場
	void Escape();											// 主角逃跑處理過場
	void StopAMoment();										// delay
	void GainGold();										// 總共獲取金錢
	void GainXp();											// 總共獲取經驗值
	void OnkeyDown(UNIT);
	void MenuControl(UNIT nChar);							// 選單介面控制
	void MenuPress(UNIT);									// 選單選擇
	void OnShow(AdjustableCInteger *NumberUI, CInteger *printNum); /* 顯示各種圖片 */
	void ShowBackground();
	void ShowMenu();
	void ShowItemMenu(CInteger *printNum);
	void ShowSkillMenu(CInteger *printNum);
	void ShowHeroLifeManaBar(CInteger *printNum);
	void ShowMonsterLifeBar(CInteger *printNum);
	void ShowCursor();
	void ShowMenuCursor();
	void ShowItemCursor();
	void ShowSkillCursor();
	void ShowAttackDamage(AdjustableCInteger *);
	void ShowBattleFinishBackground();
	void ShowHeroIcon();
	void ShowEscapefailed();
	void BackToMap(UNIT nChar);								// 返回原本地圖
	bool End();												// 結局

private:
	CMovingBitmap BattleBackground;
	CMovingBitmap FinallyBattleBackground;
	CMovingBitmap menuUI;
	CMovingBitmap AttackBtn;
	CMovingBitmap SkillBtn;
	CMovingBitmap ItemBtn;
	CMovingBitmap GuardBtn;
	CMovingBitmap EscapeBtn;
	CMovingBitmap Cursor;
	CMovingBitmap ItemMenu;
	CMovingBitmap ItemPotion;
	CMovingBitmap ItemEther;
	CMovingBitmap SkillMenu;
	CMovingBitmap SkillHeal;
	CMovingBitmap SkillLightning;
	CMovingBitmap SkillThunder;
	CMovingBitmap Back;
	CMovingBitmap BattleFinishBackground;
	CMovingBitmap heroIcon;
	CMovingBitmap EscapeFailed;
	GameMap      *map;
	Hero         *hero;
	Monster	  *monster;
	int battleBack_x, battleBack_y;							/* 各種座標 */
	int menu_x, menu_y;
	int attack_x, attack_y;
	int skill_x, skill_y;
	int item_x, item_y;
	int guard_x, guard_y;
	int escape_x, escape_y;
	int cursor_x, cursor_y;
	int itemMenu_x, itemMenu_y;
	int skillMenu_x, skillMenu_y;
	int menu_selected_x, menu_selected_y;
	int item_index, total_item;
	int item_potion_x, item_potion_y;
	int item_ether_x, item_ether_y;
	int skill_index, total_skill;
	int skill_heal_x, skill_heal_y;
	int skill_lightning_x, skill_lightning_y;
	int countTime;											// delay時間
	int heroLevel;											// 英雄等級
	bool *_isBattling;										// 戰鬥的廣播
	bool buttonIsPressed;									// 按下按鍵判斷
	bool delay;												// 判斷是否delay
	bool itemMenuIsOpen;									// 打開物品欄的判斷
	bool skillMenuIsOpen;									// 打開技能欄的判斷
	bool finishHasOpen;										// 打開結算畫面的判斷
	bool enterFoolproof;									// 防呆
	bool *playWalkTheme;									// 音效判斷
	bool escapefailedIsOpen;								// 打開逃跑失敗的判斷
	bool end;												// 結局判斷
};
}
#endif;