#ifndef LEVEL_H
#define LEVEL_H
namespace game_framework
{
class Level
{
public:
	Level();
	int GetLv();											// �^��Lv
	int GetXp();											// �^�Ǹg���
	int GetRequireXp();										// �^�Ǥɯũһݸg��
	void SetLv(int);										// �]�w����
	void SetXp(int);										// �]�w�g���
	void SetRequireXp();									// �]�w�һݸg���
private:
	int lv;
	int xp;
	int requireXp;											// �ɯũһݸg���
};
}
#endif