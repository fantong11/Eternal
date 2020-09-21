#ifndef MONSTER_H
#define MONSTER_H
#include "GameMap.h"
namespace game_framework
{
class Hero;
class Monster
{
public:
	Monster(int x, int y);
	virtual ~Monster() {};							// 解決多形的destructor沒執行到的問題
	void Initialize(int x, int y);
	int GetX1();
	int GetY1();
	int GetX2();
	int GetY2();
	int GetAttackDamage();
	int GetGold();
	int GetXp();
	int GetHp();
	int GetFullHp();
	int GetCurrentBattleState();
	void SetXY(int nx, int ny);						// 設定怪物左上角座標
	void SetHp(int HP);
	void SetHurtDamage(bool flag);					// 設定怪物受傷
	void SetMonsterDelay(bool flag);				// 開啟延遲
	virtual void StatusUpgrade(int hero_lv);		// 隨著主角等級提升強度
	bool IsDead();									// 死亡判斷
	virtual void OnMove();
	virtual void AttackHero();						// 計算怪物攻擊傷害
	virtual void SkillHero();						// 計算怪物用技能造成傷害
	void Move();
	virtual void Attack();							// 進行攻擊動畫
	virtual void Skill() = 0;						// 進行技能動畫，每個子項都不一樣所以這裡不實作
	virtual void hurt();							// 怪物受傷動畫前置動作
	void Dead();									// 進行死亡動畫
	virtual void RandomDecision(Hero &hero);		// 怪物自己行動
	virtual void StopAMoment();						// 延遲，多用於等動畫跑完
	virtual void OnShow(AdjustableCInteger *NumberUI, CInteger *printNum, GameMap *map);
	void ShowHp(int x1, int y1, int hp);
	virtual void ShowAttackDamage(AdjustableCInteger *NumberUI, GameMap *map);// 顯示怪物攻擊傷害數字
	virtual void AnimationAttack(GameMap *map);		// 怪物攻擊動畫
	virtual void AnimationHurt(GameMap *map);		// 怪物受傷動畫
	virtual void AnimationSkill(GameMap *map);		// 怪物技能動畫
	virtual void AnimationMove(GameMap *map);		// 怪物閒置動畫
	void AnimationDead(GameMap *map);				// 怪物死亡動畫

protected:
	CAnimation animation_idle;						// 怪物的動畫
	CAnimation animation_hurt;						// 怪物受傷動畫
	CAnimation animation_attack;					// 怪物攻擊動畫
	CAnimation animation_skill;						// 怪物技能東畫
	CAnimation animation_dead;						// 怪物死亡動畫
	Hero *enemy;
	int x, y;										// 怪物左上角座標
	int LV;
	int FullHp, _HP, _MP;
	int Damage;
	int DamageNum;
	int gold;
	int xp;
	int currentBattleState;							// 目前進行哪個動作
	int countTime;									// 延遲時間
	bool isAttack;									// 怪物攻擊判斷
	bool isHurt;									// 怪物受傷判斷
	bool isSkill;									// 怪物技能判斷
	bool isDead;									// 怪物死亡判斷
	bool ReallyDead;								// 死亡動畫結束
	bool delay;
	bool playSoundEffect;							// 音效
};
}
#endif