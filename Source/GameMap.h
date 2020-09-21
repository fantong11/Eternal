#ifndef GAMEMAP_H
#define GAMEMAP_H

namespace game_framework
{
class GameMap
{
public:
	GameMap();
	void LoadBitmap();										// ���J�a��
	int ScreenX(int x);										// �^�ǿù��y��X
	int ScreenY(int y);										// �^�ǿù��y��Y
	void SetLastScreenXY(int sx, int sy);					// �]�w�D���Q�ǰe�e��}
	int GetScreenX();										// �^�ǿù��y��
	int GetScreenY();										// �^�ǿù��y��
	int GetLastScreenX();									// �^�ǥD���Q�ǰe�e��}x
	int GetLastScreenY();									// �^�ǥD���Q�ǰe�e��}y
	void MoveScreenX(int x);								// �������Yx
	void MoveScreenY(int y);								// �������Yy
	void SetScreenXY(int x, int y);							// �]�w�ù��y��XY
	void SetBattleScreenXY();								// �]�w���԰��y��
	void OnShow();											// ��ܦa��
	int IsEmpty(int x, int y);								// �P�_�Y��O�_���i�H�樫����
	int GetBossDoorX();										// �^�Ǧu�@�~��}X
	int GetBossDoorY();										// �^�Ǧu�@�~��}Y
	int GetBossDoorX2();									// �^�Ǧu�@�~��}X2
	int GetBossDoorY2();									// �^�Ǧu�@�~��}Y2
protected:
	CMovingBitmap house;
	CMovingBitmap black, white, tree, tree1, tree2, tree3, tree4, tree5, tree6, tree7;
	CMovingBitmap water0, water1, water2, water3, water4;
	CMovingBitmap water5, water6, water7, water8;
	CMovingBitmap water9, water10, water11, water12;
	CMovingBitmap bridge0, bridge1, bridge2, bridge3, bridge4, bridge5;
	CMovingBitmap road0;
	CMovingBitmap boss_door;
	int map[100][35];
	const int X, Y;
	int sx, sy;												// �ù��y��
	int lastScreenX, lastScreenY;							// �ǰe�e�y��
	const int battle_sx, battle_sy;							// �԰����y��
	const int MW, MH;										// ���e��
	const int house_x, house_y;
};
}
#endif