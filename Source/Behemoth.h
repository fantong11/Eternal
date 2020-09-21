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
	void RandomDecision(Hero &hero) override;				// �H�����
	void Attack() override;									// �����ʵe
	void Skill();											// �ޯ�ʵe
	void hurt();											// ���˰ʵe
	void AttackHero() override;								// �����D���ˮ`�p��
	void OnShow(AdjustableCInteger *NumberUI, CInteger *printNum, GameMap *map) override;
	void AnimationAttack(GameMap *map) override;			// ��ܧ����ʵe
	void ShowAttackDamage(AdjustableCInteger *printNum, GameMap *map) override;
	void AnimationHurt(GameMap *map);						// ��ܨ��˰ʵe
	void AnimationMove(GameMap *map);						// ��ܶ��m�ʵe
private:
	int skillId;
	vector<unique_ptr<BehemothSkill>> skills;				// �ޯ�C
	int rush;												// �Ĩ��ܼ�
};
}
#endif // !1