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
	void StatusUpgrade(int hero_lv);					// �H�ۥD�������H�����ɱj��
	void AttackHero() override;							// �p������D���ˮ`�A�ö}�l�ʵe
	void SkillHero();									// �p��Χޯ�����D���ˮ`�A�ö}�l�ʵe
	void Attack() override;								// �i������ʵe
	void Skill() override;								// �i��ޯ�ʵe
	void AnimationSkill(GameMap *map);					// ��ܧޯ�ʵe
	void ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map);// ��ܧ����ˮ`�Ʀr
private:
	int AttackTimes;									// ��������
};
}
#endif