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
	void StatusUpgrade(int hero_lv);						// �H�ۥD�������H�����ɱj��
	void AttackHero() override;								// �p������D���ˮ`�A�ö}�l�ʵe
	void SkillHero() override;								// �p��Χޯ�����D���ˮ`�A�ö}�l�ʵe
	void Attack() override;									// �i������ʵe
	void Skill() override;									// �i��ޯ�ʵe
	void printBuff();										// ��ܼW�j
	void OnShow(AdjustableCInteger *NumberUI, CInteger *printNum, GameMap *map);
	void AnimationMove(GameMap *map);						// ��ܶ��m�ʵe
private:
	int nextAttackBuff;										// �U�@�������W�j
};
}
#endif