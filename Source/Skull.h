#ifndef SKULL_H
#define SKULL_H

#include "Monster.h"
#include "GameMap.h"

namespace game_framework
{

class Skull : public Monster
{
public:
	Skull(int x, int y, int hero_lv);
	void LoadBitmap();
	void StatusUpgrade(int hero_lv);						// 隨著主角等級隨機提升強度
	void AttackHero() override;								// 計算攻擊主角傷害，並開始動畫
	void SkillHero() override;								// 計算用技能攻擊主角傷害，並開始動畫
	void Attack() override;									// 進行攻擊動畫
	void Skill() override;									// 進行技能動畫
	void printBuff();										// 顯示增強
	void OnShow(AdjustableCInteger *NumberUI, CInteger *printNum, GameMap *map);
	void AnimationMove(GameMap *map);						// 顯示閒置動畫
private:
	int nextAttackBuff;										// 下一次攻擊增強
};
}
#endif