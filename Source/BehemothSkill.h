#ifndef BEHEMOTHSKILL_H
#define BEHEMOTHSKILL_H
#include "GameMap.h"
namespace game_framework
{
class BehemothSkill
{
public:
	BehemothSkill(int damage);
	int GetDamage();										// �^�Ƕˮ`
	int GetCurrentBitmapNumber();							// �^�ǥثe�ʵe�s��
	bool AnimationIsFinalBitmap();							// �^�ǰʵe�����S
	void AnimationReset();									// ���s�ʵe
	void OnMove();
	void OnShow(GameMap *map);
protected:
	CAnimation effect;
	int damage;
};
}
#endif