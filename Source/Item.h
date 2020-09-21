#ifndef ITEM_H
#define ITEM_H
namespace game_framework
{
class Item
{
public:
	Item(int id, int amount);
	int GetId();											// �^��Id
	int GetAmount();										// �^�Ǽƶq
	int GetCurrentBitmapNumber();							// �^�ǥثe�ʵe�и�
	void SetItemAmount(int num);							// �]�w�Ĥ��ƶq
	bool AnimationIsFinalBitmap();							// �^�ǰʵe�O�_���̫�@�i
	void AnimationReset();									// ���m�ʵe
	virtual void Use(Hero *) = 0;							// �ϥήĪG
	virtual void OnMove();
	virtual void OnShowEffect(int x, int y);				// ��ܮĪG�ʵe
	virtual void OnShowIcon(int x, int y);					// ���Icon
protected:
	CAnimation animation_effect;
	CMovingBitmap icon;
	int id;
	int amount;
};
}
#endif