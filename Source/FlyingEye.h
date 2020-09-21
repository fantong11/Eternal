#ifndef FLYINGEYE_H
#define FLYINGEYE_H
#include "Monster.h"
#include "GameMap.h"

namespace game_framework
{

class FlyingEye : public Monster
{
public:
	FlyingEye(int x, int y, int hero_lv);
	void LoadBitmap();
	void StatusUpgrade(int hero_lv);						// �H�ۥD�������H�����ɱj��
	void AttackHero() override;								// �p������D���ˮ`�A�ö}�l�ʵe
	void SkillHero() override;								// �p��Χޯ�����D���ˮ`�A�ö}�l�ʵe
	void Skill() override;									// �i��ޯ�ʵe
	void AnimationSkill(GameMap *map) override;				// ��ܧޯ�ʵe
	void ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map) override;// ��ܧ����ˮ`�Ʀr
private:
	bool Attack_1, Attack_2, Attack_3;						// �T�q�����ΧP�_
};
}
#endif