#ifndef POTION_H
#define POTION_H
#include "Item.h"
namespace game_framework
{
class Potion : public Item
{
public:
	Potion();
	void LoadBitmap();
	void Use(Hero *);										// �ϥΫ�ĪG
private:
	int heal_amount;
};
}
#endif