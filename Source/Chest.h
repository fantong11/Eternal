#pragma once
namespace game_framework
{
class Chest
{
public:
	Chest(int x, int y, int id);
	void LoadBitmap();
	void init();
	int  GetX1();										// �D�����W�� x �y��
	int  GetY1();										// �D�����W�� y �y��
	int  GetX2();										// �D���k�U�� x �y��
	int  GetY2();				 						// �D���k�U�� y �y��
	int  RandMoney();									// �H����o����
	void OnKeyDown(UNIT nChar);
	void OnMove(Hero *hero);
	void CloseWindow(Hero *hero);						// �����}��
	void Reset();
	void Delay();										// ����
	void OpenChest(Hero *hero);									// �}�_�c
	void HeroGainItem(Hero *hero);						// ���^�����~
	void OnShow(GameMap &map);
	void ShowItemGet(CInteger *printNum);				// �����o���p
	bool HasCollision(int x1, int y1, int x2, int y2);	// �I��
	bool IsOpening();									// ���b���_�c����
private:
	CAnimation open_animation;
	CMovingBitmap item_background;						// �}��BJ4
	int x, y;
	int id;
	int money;
	int delay_time;
	bool open;
	bool had_been_opened;								// �_�c�w�}�L
	bool isCollision;									// �P�_�I��
	bool delay;
	bool show_item_background;							// ��ܯ}��
	bool press_Enter;									// ���UENTER
	bool gain;											// ��o�_��
	bool finally_chest;									// �O��
};
}