#ifndef MUSHSROOM_H
#define MUSHSROOM_H
#include "Monster.h"
#include "GameMap.h"

namespace game_framework
{
class Hero;
class Mushsroom : public Monster
{
public:
	Mushsroom(int x, int y, int hero_lv);
	void LoadBitmap();
	void StatusUpgrade(int hero_lv);						// 隨著主角等級隨機提升強度
	void AttackHero() override;								// 計算攻擊主角傷害，並開始動畫
	void SkillHero() override;								// 計算用技能攻擊主角傷害，並開始動畫
	void Attack() override;									// 進行攻擊動畫
	void Skill() override;									// 進行技能動畫
	void AnimationSkill(GameMap *map) override;				// 顯示技能動畫
	void ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map) override;// 顯示攻擊傷害數字
};
}
#endif