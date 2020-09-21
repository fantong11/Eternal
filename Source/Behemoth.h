#ifndef BEHEMOTH_H
#define BEHEMOTH_H
#include <memory>
#include "BehemothSkill.h"
#include "Monster.h"
#include "GameMap.h"
using namespace std;
namespace game_framework
{
class Behemoth : public Monster
{
public:
	Behemoth();
	void LoadBitmap();
	void OnMove() override;
	void RandomDecision(Hero &hero) override;				// 隨機行動
	void Attack() override;									// 攻擊動畫
	void Skill();											// 技能動畫
	void hurt();											// 受傷動畫
	void AttackHero() override;								// 攻擊主角傷害計算
	void OnShow(AdjustableCInteger *NumberUI, CInteger *printNum, GameMap *map) override;
	void AnimationAttack(GameMap *map) override;			// 顯示攻擊動畫
	void ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map) override;
	void AnimationHurt(GameMap *map);						// 顯示受傷動畫
	void AnimationMove(GameMap *map);						// 顯示閒置動畫
private:
	int skillId;
	vector<unique_ptr<BehemothSkill>> skills;				// 技能列
	int rush;												// 衝刺變數
};
}
#endif // !1