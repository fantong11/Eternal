#ifndef GOBLIN_H
#define GOBLIN_H
#include "Monster.h"
#include "GameMap.h"

namespace game_framework
{

class Goblin : public Monster
{
public:
	Goblin(int x, int y, int hero_lv);
	void LoadBitmap();
	void StatusUpgrade(int hero_lv);					// 隨著主角等級隨機提升強度
	void AttackHero() override;							// 計算攻擊主角傷害，並開始動畫
	void SkillHero();									// 計算用技能攻擊主角傷害，並開始動畫
	void Attack() override;								// 進行攻擊動畫
	void Skill() override;								// 進行技能動畫
	void AnimationSkill(GameMap *map);					// 顯示技能動畫
	void ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map);// 顯示攻擊傷害數字
private:
	int AttackTimes;									// 攻擊次數
};
}
#endif