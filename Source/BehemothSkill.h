#ifndef BEHEMOTHSKILL_H
#define BEHEMOTHSKILL_H
#include "GameMap.h"
namespace game_framework
{
class BehemothSkill
{
public:
	BehemothSkill(int damage);
	int GetDamage();										// 回傳傷害
	int GetCurrentBitmapNumber();							// 回傳目前動畫編號
	bool AnimationIsFinalBitmap();							// 回傳動畫結束沒
	void AnimationReset();									// 重製動畫
	void OnMove();
	void OnShow(GameMap *map);
protected:
	CAnimation effect;
	int damage;
};
}
#endif