#ifndef NPC_H
#define NPC_H
#include "GameMap.h"
namespace game_framework
{
typedef unsigned int UNIT;
class Npc
{
public:
	Npc(int x, int y, int endPos, int direction, Hero *hero);
	void Initialize(int x, int y, int endPos, int direction, Hero *hero);// �]�w�D������l��
	void LoadBitmap();									// ���J�ϧ�
	int  GetX1();										// �D�����W�� x �y��
	int  GetY1();										// �D�����W�� y �y��
	int  GetX2();										// �D���k�U�� x �y��
	int  GetY2();				 						// �D���k�U�� y �y��
	void SetXY(int nx, int ny);							// �]�w�D�����W���y��
	void SetMovingDown(bool flag);						// �]�w�O�_���b���U����
	void SetMovingLeft(bool flag);						// �]�w�O�_���b��������
	void SetMovingRight(bool flag);						// �]�w�O�_���b���k����
	void SetMovingUp(bool flag);						// �]�w�O�_���b���W����
	void SetAllMovingToFalse();							// �]�w����
	void SetAllMovingToTrue();							// �]�w�i�H����
	bool isMoving();
	void OnMove(GameMap *map);							// ���ʥD��
	void SetMovingState(int flag);						// �]�w��V �� = 0, �k = 1, �W = 2, �U = 3
	bool HasCollision(int x1, int y1, int x2, int y2);
	void NoCollisionTurnOffAllThing();					// �����Ҧ����I���ܼ�
	bool IsRespone();									// �^�Ƕi�J��ܡA������L�ʧ@��
	void movingArea(GameMap *map);						// ���ʽd��
	void StopAMoment(CAnimation &, bool &, bool &);		// ����
	void OnShow(GameMap *map, CInteger *printNum);		// ��ܥD��
	void AnimationMove(GameMap *map);
	void ShowSpeechBubble(GameMap *map, CInteger *);	// ��ܹ�ܪ��I���}��
	void ShowResponeUI();								// ��ܦ^���ﶵ���I���}��
	void ShowCursor();									// ����ݼ�
	void ShowShopUI();									// �K�W�ťժ��I���A�\����ܪ��}��
	void ShowShopItem(CInteger *, CDC *);				// ��ܰө��c�⪺���~
	void ShowBlacksmith(CInteger *, CDC *);				// ����K�K�Q
	void ShowPauper();									// ��ܿ�������
	void talk(GameMap *, CInteger *);					// ��ܹ��
	void CursorControl(UNIT nChar);						// �����
	void OnkeyDown(UINT nChar);
	void Respone(UNIT nChar);							// �^�����ﶵ�ʧ@
	void Shopping(UNIT nChar);							// �D�諸�ʧ@
	void BuySomeThing(UNIT nChar);						// �ʶR���ʧ@
protected:
	CAnimation animation_U;								// NPC�W�����ʵe
	CAnimation animation_D;								// NPC�U�����ʵe
	CAnimation animation_L;								// NPC�������ʵe
	CAnimation animation_R;								// NPC�k�����ʵe
	CMovingBitmap shopUI;								// �ө��I��
	CMovingBitmap speechBubble;							// ��ѭI��
	CMovingBitmap responeUI;							// �^�ЬO�Χ_
	CMovingBitmap Cursor;
	int  x, y;											// NPC���W���y��
	int cursor_x, cursor_y;
	int  STEP_SIZE;										// ���ʶZ��
	int  lastMovingState;
	int  startPos;										// ���ʰ_�I
	int  endPos;										// ���ʲ��I
	int  direction;										// ���¤�V
	int  countTime;
	int  talkId;										// �����e
	int  menuId;										// ���Хثe�ҦbId
	int  respone;										// �^����Index
	bool isMovingDown;									// �O�_���b���U����
	bool isMovingLeft;									// �O�_���b��������
	bool isMovingRight;									// �O�_���b���k����
	bool isMovingUp;									// �O�_���b���W����
	bool isCollision;
	bool enterFoolproof;								// ���b��
	bool openSpeechBubble;								// �P�_���}��ܭI�����ܼ�
	bool openShopUI;									// �P�_���}�ө��I�����ܼ�
	bool openResponeUI;									// �P�_���}�ﶵ�I�����ܼ�
	bool InPotionShop;									// �b�Ĥ���
	bool InBlacksmith;									// �b�K�K�Q
	bool openTalk;										// ��ܹ��
	bool Pauper;										// ��ܿ��������P�_
	Hero  *hero;
};
}
#endif