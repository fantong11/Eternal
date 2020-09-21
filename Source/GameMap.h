#ifndef GAMEMAP_H
#define GAMEMAP_H

namespace game_framework
{
class GameMap
{
public:
	GameMap();
	void LoadBitmap();										// 載入地圖
	int ScreenX(int x);										// 回傳螢幕座標X
	int ScreenY(int y);										// 回傳螢幕座標Y
	void SetLastScreenXY(int sx, int sy);					// 設定主角被傳送前位址
	int GetScreenX();										// 回傳螢幕座標
	int GetScreenY();										// 回傳螢幕座標
	int GetLastScreenX();									// 回傳主角被傳送前位址x
	int GetLastScreenY();									// 回傳主角被傳送前位址y
	void MoveScreenX(int x);								// 移動鏡頭x
	void MoveScreenY(int y);								// 移動鏡頭y
	void SetScreenXY(int x, int y);							// 設定螢幕座標XY
	void SetBattleScreenXY();								// 設定成戰鬥座標
	void OnShow();											// 顯示地圖
	int IsEmpty(int x, int y);								// 判斷某格是否為可以行走的路
	int GetBossDoorX();										// 回傳守護獸位址X
	int GetBossDoorY();										// 回傳守護獸位址Y
	int GetBossDoorX2();									// 回傳守護獸位址X2
	int GetBossDoorY2();									// 回傳守護獸位址Y2
protected:
	CMovingBitmap house;
	CMovingBitmap black, white, tree, tree1, tree2, tree3, tree4, tree5, tree6, tree7;
	CMovingBitmap water0, water1, water2, water3, water4;
	CMovingBitmap water5, water6, water7, water8;
	CMovingBitmap water9, water10, water11, water12;
	CMovingBitmap bridge0, bridge1, bridge2, bridge3, bridge4, bridge5;
	CMovingBitmap road0;
	CMovingBitmap boss_door;
	int map[100][35];
	const int X, Y;
	int sx, sy;												// 螢幕座標
	int lastScreenX, lastScreenY;							// 傳送前座標
	const int battle_sx, battle_sy;							// 戰鬥場座標
	const int MW, MH;										// 方格寬高
	const int house_x, house_y;
};
}
#endif