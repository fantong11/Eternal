#ifndef MONSTER_H
#define MONSTER_H
#include "GameMap.h"
namespace game_framework
{
class Hero;
class Monster
{
public:
	Monster(int x, int y);
	virtual ~Monster() {};							// �ѨM�h�Ϊ�destructor�S����쪺���D
	void Initialize(int x, int y);
	int GetX1();
	int GetY1();
	int GetX2();
	int GetY2();
	int GetAttackDamage();
	int GetGold();
	int GetXp();
	int GetHp();
	int GetFullHp();
	int GetCurrentBattleState();
	void SetXY(int nx, int ny);						// �]�w�Ǫ����W���y��
	void SetHp(int HP);
	void SetHurtDamage(bool flag);					// �]�w�Ǫ�����
	void SetMonsterDelay(bool flag);				// �}�ҩ���
	virtual void StatusUpgrade(int hero_lv);		// �H�ۥD�����Ŵ��ɱj��
	bool IsDead();									// ���`�P�_
	virtual void OnMove();
	virtual void AttackHero();						// �p��Ǫ������ˮ`
	virtual void SkillHero();						// �p��Ǫ��Χޯ�y���ˮ`
	void Move();
	virtual void Attack();							// �i������ʵe
	virtual void Skill() = 0;						// �i��ޯ�ʵe�A�C�Ӥl�������@�˩ҥH�o�̤���@
	virtual void hurt();							// �Ǫ����˰ʵe�e�m�ʧ@
	void Dead();									// �i�榺�`�ʵe
	virtual void RandomDecision(Hero &hero);		// �Ǫ��ۤv���
	virtual void StopAMoment();						// ����A�h�Ω󵥰ʵe�]��
	virtual void OnShow(AdjustableCInteger *NumberUI, CInteger *printNum, GameMap *map);
	void ShowHp(int x1, int y1, int hp);
	virtual void ShowAttackDamage(AdjustableCInteger *NumberUI, GameMap *map);// ��ܩǪ������ˮ`�Ʀr
	virtual void AnimationAttack(GameMap *map);		// �Ǫ������ʵe
	virtual void AnimationHurt(GameMap *map);		// �Ǫ����˰ʵe
	virtual void AnimationSkill(GameMap *map);		// �Ǫ��ޯ�ʵe
	virtual void AnimationMove(GameMap *map);		// �Ǫ����m�ʵe
	void AnimationDead(GameMap *map);				// �Ǫ����`�ʵe

protected:
	CAnimation animation_idle;						// �Ǫ����ʵe
	CAnimation animation_hurt;						// �Ǫ����˰ʵe
	CAnimation animation_attack;					// �Ǫ������ʵe
	CAnimation animation_skill;						// �Ǫ��ޯ�F�e
	CAnimation animation_dead;						// �Ǫ����`�ʵe
	Hero *enemy;
	int x, y;										// �Ǫ����W���y��
	int LV;
	int FullHp, _HP, _MP;
	int Damage;
	int DamageNum;
	int gold;
	int xp;
	int currentBattleState;							// �ثe�i����Ӱʧ@
	int countTime;									// ����ɶ�
	bool isAttack;									// �Ǫ������P�_
	bool isHurt;									// �Ǫ����˧P�_
	bool isSkill;									// �Ǫ��ޯ�P�_
	bool isDead;									// �Ǫ����`�P�_
	bool ReallyDead;								// ���`�ʵe����
	bool delay;
	bool playSoundEffect;							// ����
};
}
#endif