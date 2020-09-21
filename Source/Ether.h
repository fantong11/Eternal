#ifndef ETHER_H
#define ETHER_H
#include "Item.h"

namespace game_framework
{
class Ether : public Item
{
public:
	Ether();
	void LoadBitmap();
	void Use(Hero *);										// �ϥΫ�ĪG
	void OnShowEffect(int x, int y);						// ��ܮĪG�ʵe
	void OnShowIcon(int x, int y) override;					// ���Icon
private:
	int heal_amount;										// �D��ƶq
};
}
#endif