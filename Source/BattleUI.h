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
	void Attack();											// �D�������B�z�L��
	void Skill(UNIT);										// �D���ޯ�B�z�L��
	void SkillPress(UNIT);									// �ޯ���
	void Item(UNIT);										// �D���ϥιD��B�z�L��
	void ItemPress(UNIT);									// ���~���
	void Guard();											// �D�����m�B�z�L��
	void Escape();											// �D���k�]�B�z�L��
	void StopAMoment();										// delay
	void GainGold();										// �`�@�������
	void GainXp();											// �`�@����g���
	void OnkeyDown(UNIT);
	void MenuControl(UNIT nChar);							// ��椶������
	void MenuPress(UNIT);									// �����
	void OnShow(AdjustableCInteger *NumberUI, CInteger *printNum); /* ��ܦU�عϤ� */
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
	void BackToMap(UNIT nChar);								// ��^�쥻�a��
	bool End();												// ����

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
	int battleBack_x, battleBack_y;							/* �U�خy�� */
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
	int countTime;											// delay�ɶ�
	int heroLevel;											// �^������
	bool *_isBattling;										// �԰����s��
	bool buttonIsPressed;									// ���U����P�_
	bool delay;												// �P�_�O�_delay
	bool itemMenuIsOpen;									// ���}���~�檺�P�_
	bool skillMenuIsOpen;									// ���}�ޯ��檺�P�_
	bool finishHasOpen;										// ���}����e�����P�_
	bool enterFoolproof;									// ���b
	bool *playWalkTheme;									// ���ħP�_
	bool escapefailedIsOpen;								// ���}�k�]���Ѫ��P�_
	bool end;												// �����P�_
};
}
#endif;