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
	void StatusUpgrade(int hero_lv);						// �H�ۥD�������H�����ɱj��
	void AttackHero() override;								// �p������D���ˮ`�A�ö}�l�ʵe
	void SkillHero() override;								// �p��Χޯ�����D���ˮ`�A�ö}�l�ʵe
	void Attack() override;									// �i������ʵe
	void Skill() override;									// �i��ޯ�ʵe
	void AnimationSkill(GameMap *map) override;				// ��ܧޯ�ʵe
	void ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map) override;// ��ܧ����ˮ`�Ʀr
};
}
#endif