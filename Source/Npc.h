#ifndef NPC_H
#define NPC_H
#include "GameMap.h"
namespace game_framework
{
typedef unsigned int UNIT;
class Npc
{
public:
	Npc(int x, int y, int endPos, int direction, Hero *hero);
	void Initialize(int x, int y, int endPos, int direction, Hero *hero);// 設定主角為初始值
	void LoadBitmap();									// 載入圖形
	int  GetX1();										// 主角左上角 x 座標
	int  GetY1();										// 主角左上角 y 座標
	int  GetX2();										// 主角右下角 x 座標
	int  GetY2();				 						// 主角右下角 y 座標
	void SetXY(int nx, int ny);							// 設定主角左上角座標
	void SetMovingDown(bool flag);						// 設定是否正在往下移動
	void SetMovingLeft(bool flag);						// 設定是否正在往左移動
	void SetMovingRight(bool flag);						// 設定是否正在往右移動
	void SetMovingUp(bool flag);						// 設定是否正在往上移動
	void SetAllMovingToFalse();							// 設定不動
	void SetAllMovingToTrue();							// 設定可以移動
	bool isMoving();
	void OnMove(GameMap *map);							// 移動主角
	void SetMovingState(int flag);						// 設定方向 左 = 0, 右 = 1, 上 = 2, 下 = 3
	bool HasCollision(int x1, int y1, int x2, int y2);
	void NoCollisionTurnOffAllThing();					// 關掉所有的碰撞變數
	bool IsRespone();									// 回傳進入對話，關閉其他動作用
	void movingArea(GameMap *map);						// 移動範圍
	void StopAMoment(CAnimation &, bool &, bool &);		// 延遲
	void OnShow(GameMap *map, CInteger *printNum);		// 顯示主角
	void AnimationMove(GameMap *map);
	void ShowSpeechBubble(GameMap *map, CInteger *);	// 顯示對話的背景破布
	void ShowResponeUI();								// 顯示回答選項的背景破布
	void ShowCursor();									// 顯示屬標
	void ShowShopUI();									// 貼上空白的背景，蓋掉對話的破布
	void ShowShopItem(CInteger *, CDC *);				// 顯示商店販售的物品
	void ShowBlacksmith(CInteger *, CDC *);				// 顯示鐵匠鋪
	void ShowPauper();									// 顯示錢不夠用
	void talk(GameMap *, CInteger *);					// 顯示對話
	void CursorControl(UNIT nChar);						// 控制鼠標
	void OnkeyDown(UINT nChar);
	void Respone(UNIT nChar);							// 回答的選項動作
	void Shopping(UNIT nChar);							// 挑選的動作
	void BuySomeThing(UNIT nChar);						// 購買的動作
protected:
	CAnimation animation_U;								// NPC上走的動畫
	CAnimation animation_D;								// NPC下走的動畫
	CAnimation animation_L;								// NPC左走的動畫
	CAnimation animation_R;								// NPC右走的動畫
	CMovingBitmap shopUI;								// 商店背景
	CMovingBitmap speechBubble;							// 聊天背景
	CMovingBitmap responeUI;							// 回覆是或否
	CMovingBitmap Cursor;
	int  x, y;											// NPC左上角座標
	int cursor_x, cursor_y;
	int  STEP_SIZE;										// 移動距離
	int  lastMovingState;
	int  startPos;										// 移動起點
	int  endPos;										// 移動終點
	int  direction;										// 面朝方向
	int  countTime;
	int  talkId;										// 對話邊畫
	int  menuId;										// 鼠標目前所在Id
	int  respone;										// 回答的Index
	bool isMovingDown;									// 是否正在往下移動
	bool isMovingLeft;									// 是否正在往左移動
	bool isMovingRight;									// 是否正在往右移動
	bool isMovingUp;									// 是否正在往上移動
	bool isCollision;
	bool enterFoolproof;								// 防呆用
	bool openSpeechBubble;								// 判斷打開對話背景的變數
	bool openShopUI;									// 判斷打開商店背景的變數
	bool openResponeUI;									// 判斷打開選項背景的變數
	bool InPotionShop;									// 在藥水店
	bool InBlacksmith;									// 在鐵匠鋪
	bool openTalk;										// 顯示對話
	bool Pauper;										// 顯示錢不夠的判斷
	Hero  *hero;
};
}
#endif