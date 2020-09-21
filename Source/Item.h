#ifndef ITEM_H
#define ITEM_H
namespace game_framework
{
class Item
{
public:
	Item(int id, int amount);
	int GetId();											// 回傳Id
	int GetAmount();										// 回傳數量
	int GetCurrentBitmapNumber();							// 回傳目前動畫標號
	void SetItemAmount(int num);							// 設定藥水數量
	bool AnimationIsFinalBitmap();							// 回傳動畫是否為最後一張
	void AnimationReset();									// 重置動畫
	virtual void Use(Hero *) = 0;							// 使用效果
	virtual void OnMove();
	virtual void OnShowEffect(int x, int y);				// 顯示效果動畫
	virtual void OnShowIcon(int x, int y);					// 顯示Icon
protected:
	CAnimation animation_effect;
	CMovingBitmap icon;
	int id;
	int amount;
};
}
#endif