#ifndef SKILL_H
#define SKILL_H
namespace game_framework
{
class Skill
{
public:
	Skill(int id, int manaCost);
	int GetId();											// 回傳技能編號
	int GetManaCost();										// 回傳耗魔量
	int GetDamage();										// 回傳技能傷害
	bool AnimationIsFinalBitmap();							// 回傳動畫結束
	void AnimationReset();									// 重製動畫
	void OnMove();
	void OnShowEffect(GameMap *);							// 顯示效果動畫

protected:
	CAnimation animation_effect;
	int id;
	int manaCost;
	int damage;
	int x, y;
};
}
#endif