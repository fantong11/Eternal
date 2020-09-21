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
	void Use(Hero *);										// 使用後效果
	void OnShowEffect(int x, int y);						// 顯示效果動畫
	void OnShowIcon(int x, int y) override;					// 顯示Icon
private:
	int heal_amount;										// 道具數量
};
}
#endif