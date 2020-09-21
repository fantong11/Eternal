#ifndef LEVEL_H
#define LEVEL_H
namespace game_framework
{
class Level
{
public:
	Level();
	int GetLv();											// 回傳Lv
	int GetXp();											// 回傳經驗值
	int GetRequireXp();										// 回傳升級所需經驗
	void SetLv(int);										// 設定等級
	void SetXp(int);										// 設定經驗值
	void SetRequireXp();									// 設定所需經驗值
private:
	int lv;
	int xp;
	int requireXp;											// 升級所需經驗值
};
}
#endif