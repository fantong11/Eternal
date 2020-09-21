#pragma once
namespace game_framework
{
class Chest
{
public:
	Chest(int x, int y, int id);
	void LoadBitmap();
	void init();
	int  GetX1();										// 主角左上角 x 座標
	int  GetY1();										// 主角左上角 y 座標
	int  GetX2();										// 主角右下角 x 座標
	int  GetY2();				 						// 主角右下角 y 座標
	int  RandMoney();									// 隨機獲得金錢
	void OnKeyDown(UNIT nChar);
	void OnMove(Hero *hero);
	void CloseWindow(Hero *hero);						// 關閉破布
	void Reset();
	void Delay();										// 延遲
	void OpenChest(Hero *hero);									// 開寶箱
	void HeroGainItem(Hero *hero);						// 給英雄物品
	void OnShow(GameMap &map);
	void ShowItemGet(CInteger *printNum);				// 顯示獲得殺小
	bool HasCollision(int x1, int y1, int x2, int y2);	// 碰撞
	bool IsOpening();									// 正在跟寶箱互動
private:
	CAnimation open_animation;
	CMovingBitmap item_background;						// 破布BJ4
	int x, y;
	int id;
	int money;
	int delay_time;
	bool open;
	bool had_been_opened;								// 寶箱已開過
	bool isCollision;									// 判斷碰撞
	bool delay;
	bool show_item_background;							// 顯示破布
	bool press_Enter;									// 按下ENTER
	bool gain;											// 獲得寶物
	bool finally_chest;									// 保底
};
}