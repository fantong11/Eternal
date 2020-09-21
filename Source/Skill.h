#ifndef SKILL_H
#define SKILL_H
namespace game_framework
{
class Skill
{
public:
	Skill(int id, int manaCost);
	int GetId();											// �^�ǧޯ�s��
	int GetManaCost();										// �^�ǯ��]�q
	int GetDamage();										// �^�ǧޯ�ˮ`
	bool AnimationIsFinalBitmap();							// �^�ǰʵe����
	void AnimationReset();									// ���s�ʵe
	void OnMove();
	void OnShowEffect(GameMap *);							// ��ܮĪG�ʵe

protected:
	CAnimation animation_effect;
	int id;
	int manaCost;
	int damage;
	int x, y;
};
}
#endif