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
	void Use(Hero *);										// 使用後效果
private:
	int heal_amount;
};
}
#endif