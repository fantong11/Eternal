#include "Skull.h"
#include "FlyingEye.h"
#include "Goblin.h"
#include "Mushsroom.h"
#include "Behemoth.h"
#include "Monster.h"
#include "Hero.h"
#include "Npc.h"
#include "Chest.h"
#include "GameMap.h"
#include "BattleUI.h"

namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////

enum AUDIO_ID  			// 定義各種音效的編號
{
	AUDIO_WALK_THEME,	// 0
	AUDIO_BATTLE,		// 1
	AUDIO_SELECT,
	AUDIO_SWORD,
	AUDIO_SPELL,
	AUDIO_LIGHTNING,
	AUDIO_LASER,
	AUDIO_HIT,
	AUDIO_VICTORY_THEME,
	AUDIO_BEHEMOTH_THEME,
	AUDIO_DUTY_VICTORY,
	AUDIO_MAIN_MENU
};

enum MONSTER_ID  			// 怪物ID
{
	MONSTER_SKULL,
	MONSTER_FlyingEye,
	MONSTER_GOBLIN,
	MONSTER_MUSHSROOM,
	BOSS_BEHEMOTH
};

static bool result = false;
static bool loadReadlly = false;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateInit : public CGameState
{
public:
	CGameStateInit(CGame *g);
	void OnInit();  								// 遊戲的初值及圖形設定
	void OnBeginState();							// 設定每次重玩所需的變數
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnShowBackground();						// 顯示背景
	void OnShowCursor();							// 顯示開始畫面的鼠標
	void OnShowTutorial();							// 顯示操作方法與密技
	void OnShowAbout();								// 顯示關於
	void OnShowStoryBackground();					// 顯示劇情背景
	void OnShowStory();								// 顯示劇情
	void runText(char *a, char *b, int amount);		// 跑條
protected:
	void OnShow();									// 顯示這個狀態的遊戲畫面
private:											// 各種圖標
	CMovingBitmap Title;
	CMovingBitmap Start;
	CMovingBitmap TutorialFont;
	CMovingBitmap About;
	CMovingBitmap Exit;
	CMovingBitmap Cursor;							// 鼠標
	CMovingBitmap Tutorial;							// 操作說明鄭張圖
	CMovingBitmap AboutBtn;							// 關於
	CMovingBitmap Story;							// 劇情
	CMovingBitmap Background;						// 背景
	CMovingBitmap Actress;							// 女主角
	CMovingBitmap Actor;							// 主角
	CMovingBitmap Temp1;							// 跑龍套的
	CMovingBitmap Temp2;							// 跑龍套的
	CMovingBitmap Temp3;							// 跑龍套的
	CMovingBitmap Temp4;							// 跑龍套的
	int cursor_x, cursor_y;
	int menu_index;
	int total_menu;
	int about_y;
	int story;
	int i;
	char t1[80] = "";
	char t2[80] = "";
	char t3[80] = "";
	char t4[80] = "";
	char t5[80] = "";
	char t6[80] = "";
	bool tutorialIsOpen;
	bool enterFoolproof;
	bool aboutIsOpen;
	bool storyIsOpen;
	bool jumpStory;									// 跳過劇情
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState
{
public:
	CGameStateRun(CGame *g);
	~CGameStateRun();
	void OnBeginState();				// 設定每次重玩所需的變數
	void OnInit();  					// 遊戲的初值及圖形設定
	void OnKeyDown(UINT, UINT, UINT);
	void OnKeyUp(UINT, UINT, UINT);
	void End();
protected:
	bool DoingSomeing();
	void OnMove();						// 移動遊戲元素
	void OnBattle();
	void OnAudio();
	Monster *RandomMonster();
	void OnShow();						// 顯示這個狀態的遊戲畫面
	void ShowHeroUi();
private:
	BattleUI			battleUI;		// 戰鬥介面
	Hero				hero;			// 拍子
	Monster				*monster;		// 怪物
	Skull				*skull;			// 骨髏
	FlyingEye			*flyingEye;	    // 蜘蛛
	Goblin				*goblin;		// 哥布林
	Mushsroom			*mushsroom;		// 香菇人
	Behemoth            *behemoth;
	vector<unique_ptr<Npc>>	npc;		// 商人
	vector<unique_ptr<Chest>>	chest;
	CInteger			printNum;		// 生命
	AdjustableCInteger	NumberUI;
	GameMap				gamemap;		// 地圖
	bool				isBattling;
	bool				isCollision;
	bool				playWalkTheme;
	bool				end;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState
{
public:
	CGameStateOver(CGame *g);
	void OnBeginState();	  	// 設定每次重玩所需的變數
	void OnInit();
protected:
	void OnMove();			  	// 移動遊戲元素
	void OnShow();			  	// 顯示這個狀態的遊戲畫面
private:
	CMovingBitmap Background;
	int counter;				// 倒數之計數器
};

}