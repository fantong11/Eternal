#ifndef HERO_H
#define HERO_H
#include <vector>
#include "Skull.h"
#include "GameMap.h"
#include "Level.h"
#include "Item.h"
#include "Skill.h"
#include "Npc.h"
#include "Chest.h"
#include <memory>
namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// 這個class提供可以用鍵盤或滑鼠控制的主角
// 看懂就可以改寫成自己的程式了
/////////////////////////////////////////////////////////////////////////////
typedef unsigned int UNIT;
class Hero
{
public:
	Hero();
	void Initialize(bool *, vector<unique_ptr<Npc>> *npc, vector<unique_ptr<Chest>> *chest);// 設定主角為初始值
	void LoadBitmap();										// 載入圖形
	int  GetX1();											// 主角左上角 x 座標
	int  GetY1();											// 主角左上角 y 座標
	int  GetX2();											// 主角右下角 x 座標
	int  GetY2();											// 主角右下角 y 座標
	int  GetSizeX();
	int  GetSizeY();
	int  GetMaxHp();
	int  GetMaxMp();
	int  GetHp();
	int  GetMp();
	int  GetLastPositionX();								// 回傳上次座標
	int  GetLastPositionY();								// 回傳上次座標
	int  GetAttackDamage();									// 回傳攻擊傷害
	int  GetWeaponGrade();									// 回傳武器等級
	int  GetArmorGrade();									// 回傳防具等級
	int  GetShieldGrade();									// 回傳盾牌等級
	int  GetSkillDamage();									// 回傳技能傷害
	int  GetCurrentBattleState();							// 回傳目前狀態，狀態有閒置，攻擊，防禦，技能
	int  GetGold();											// 回傳金錢
	int  GetLevel();										// 回傳等級
	int  GetItemAmount(int);								// 回傳道具數量
	int  GetSkillManaCost(int);								// 回傳技能耗魔量
	int  GetBlockDamage();									// 回傳隔擋傷害量
	int  GetTreasureAmount();								// 回傳寶物數量
	int  GetFinallyChest();									// 回傳保底數
	void SetXY(int nx, int ny);								// 設定主角左上角座標
	void SetLastXY(int nx, int ny);							// 紀錄主角移動前座標
	void SetHp(int HP);										// 設定血量
	void SetMp(int MP);										// 設定魔量
	void SetMovingDown(bool flag);							// 設定是否正在往下移動
	void SetMovingLeft(bool flag);							// 設定是否正在往左移動
	void SetMovingRight(bool flag);							// 設定是否正在往右移動
	void SetMovingUp(bool flag);							// 設定是否正在往上移動
	void SetAllMovingToFalse();								// 設定不動
	void SetMovingState(int flag);							// 設定方向 左 = 0, 右 = 1, 上 = 2, 下 = 3
	void SetMoveDistance(int dst);							// 設定移動距離
	void SetRun(bool);										// 設定開始跑步
	void SetGuard(bool);									// 設定防禦
	void SetGold(int);										// 設定獲得金錢
	void SetXp(int xp);										// 獲得經驗值
	void SetLevel();										// 改變等級
	void SetItemAmount(int id, int amount);					// 設定物品數量
	void SetWeaponGrade(int);								// 設定武器等級
	void SetArmorGrade(int);								// 設定防具等級
	void SetShieldGrade(int);								// 設定盾牌等級
	void SetTreasureAmount(int);							// 設定神器數量
	void SetFinallyBattleEnd(bool flag);					// 戰鬥結束關閉
	void SetFinallyChest(int);								// 設置保底數
	void OpenBossDoor();									// 打開守護獸門
	void LevelUp();											// 等級提升
	bool NextStepIsEmpty(GameMap *map, bool movingState, int x1, int y1, int x2, int y2);	// 判斷下一格是否可以走
	bool HasMeetMonster(GameMap *map);						// 遇到怪物
	bool isMoving();										// 正在移動
	bool isGuarding();										// 正在防禦
	bool IsCollisionNpc();									// 碰撞到npc
	bool IsCollisionChest();								// 碰撞到寶箱
	bool HasCollision(int x1, int y1, int x2, int y2, GameMap *map);		// 判斷是否碰撞到
	bool IsRespone();										// 在選擇中
	bool GetReadllyFight();
	void OnMove(GameMap *map);								// 移動主角
	void Moving(GameMap *map);								// 移動動畫
	void Attacking();										// 攻擊動畫
	void AttackMonster(Monster &);							// 攻擊怪物
	void SkillAttackMonster(Monster &, int);				// 技能攻擊怪物
	void Guarding();										// 防禦動畫
	void Healing();											// 回復動畫
	void UseItem(int);										// 輸入要使用的道具編號
	void Skilling();										// 技能動畫
	void OnKeyDown(UNIT nChar);
	void OnKeyUp(UNIT nChar);
	void OnShow(GameMap *map, AdjustableCInteger *printNum, CInteger *printNum2);// 顯示主角
	void doStandingAnimation(GameMap *map);					// 停住不動時
	void AnimationMove(GameMap *map);						// 顯示移動動畫
	void AnimationAttack(GameMap *map);						// 顯示攻擊動畫
	void AnimationGuard(GameMap *map);						// 顯示防禦動畫
	void AnimationGuardReset();								// 顯示防禦動畫重置
	void AnimationHeal(GameMap *map);						// 顯示回復動畫
	void AnimationSkill(GameMap *map);						// 顯示技能動畫
	void ShowUI(GameMap *map, AdjustableCInteger *printNum);// 顯示閒置介面
	void ShowHeroUI(GameMap *map, AdjustableCInteger *printNum);// 顯示基礎數值介面
	void ShowGoldUI(GameMap *map, AdjustableCInteger *printNum);// 顯示金錢介面
	void PrintNumber(GameMap *map, AdjustableCInteger *printNum, int number, int nx, int ny);// 顯示數字
	void ShowHp(int x1, int y1, int hp);					// 顯示血量
	void ShowMp(int x1, int y1, int mp);					// 顯示魔量
	void ShowXp(int x1, int y1, int xp, int requireXp);		// 顯示經驗值
	void ShowPotion(GameMap *map, AdjustableCInteger *printNum);
protected:
	CAnimation animation_U;									// 主角上走的動畫
	CAnimation animation_D;									// 主角下走的動畫
	CAnimation animation_L;									// 主角左走的動畫
	CAnimation animation_R;									// 主角右走的動畫
	CAnimation animation_attack;
	CAnimation animation_guard;
	CMovingBitmap HP_UI;
	CMovingBitmap Gold_UI;
	CMovingBitmap BossDoorFailed;
	int  x, y;												// 主角左上角座標
	int _HP, MaxHp, _MP, MaxMp;
	int  lastPosition_x, lastPosition_y;					// 上一個位置
	int  STEP_SIZE;											// 移動距離
	int  RUN_SIZE;											// 跑步距離
	int  lastMovingState;									// 上個移動方向
	int  currentBattleState;								// 目前行動狀態
	int  weapon_grade;										// 武器等級
	int  armor_grade;										// 防具等級
	int  shield_grade;										// 盾牌等級
	int  AttackDamage;
	int  SkillDamage;
	int  blockDamage;										// 格擋傷害
	int  moveDistance;										// 移動距離
	int  Gold;
	int  itemId, skillId;
	int  treasure;											// 寶物數量
	int  finally_chest;										// 保底
	bool isMovingDown;										// 是否正在往下移動
	bool isMovingLeft;										// 是否正在往左移動
	bool isMovingRight;										// 是否正在往右移動
	bool isMovingUp;										// 是否正在往上移動
	bool isRunning;
	bool *_isBattling;										// 是否戰鬥中
	bool isAttack;
	bool isGuard;
	bool isHeal;
	bool isSkill;
	bool isPressEnter;										// 選擇開寶箱
	bool isInFrontOfBoss_door;								// 在守護獸門口前
	bool readllyFight;										// 準備好最後一戰
	Level level;
	vector<unique_ptr<Item>> items;
	vector<unique_ptr<Skill>> skills;
	vector<unique_ptr<Npc>> *npc;
	vector<unique_ptr<Chest>> *chest;
};
}
#endif