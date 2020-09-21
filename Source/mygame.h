#include "Skull.h"
#include "FlyingEye.h"
#include "Goblin.h"
#include "Mushsroom.h"
#include "Behemoth.h"
#include "Monster.h"
#include "Hero.h"
#include "Npc.h"
#include "Chest.h"
#include "GameMap.h"
#include "BattleUI.h"

namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////

enum AUDIO_ID  			// �w�q�U�ح��Ī��s��
{
	AUDIO_WALK_THEME,	// 0
	AUDIO_BATTLE,		// 1
	AUDIO_SELECT,
	AUDIO_SWORD,
	AUDIO_SPELL,
	AUDIO_LIGHTNING,
	AUDIO_LASER,
	AUDIO_HIT,
	AUDIO_VICTORY_THEME,
	AUDIO_BEHEMOTH_THEME,
	AUDIO_DUTY_VICTORY,
	AUDIO_MAIN_MENU
};

enum MONSTER_ID  			// �Ǫ�ID
{
	MONSTER_SKULL,
	MONSTER_FlyingEye,
	MONSTER_GOBLIN,
	MONSTER_MUSHSROOM,
	BOSS_BEHEMOTH
};

static bool result = false;
static bool loadReadlly = false;
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateInit : public CGameState
{
public:
	CGameStateInit(CGame *g);
	void OnInit();  								// �C������Ȥιϧγ]�w
	void OnBeginState();							// �]�w�C�������һݪ��ܼ�
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnShowBackground();						// ��ܭI��
	void OnShowCursor();							// ��ܶ}�l�e��������
	void OnShowTutorial();							// ��ܾާ@��k�P�K��
	void OnShowAbout();								// �������
	void OnShowStoryBackground();					// ��ܼ@���I��
	void OnShowStory();								// ��ܼ@��
	void runText(char *a, char *b, int amount);		// �]��
protected:
	void OnShow();									// ��ܳo�Ӫ��A���C���e��
private:											// �U�عϼ�
	CMovingBitmap Title;
	CMovingBitmap Start;
	CMovingBitmap TutorialFont;
	CMovingBitmap About;
	CMovingBitmap Exit;
	CMovingBitmap Cursor;							// ����
	CMovingBitmap Tutorial;							// �ާ@�����G�i��
	CMovingBitmap AboutBtn;							// ����
	CMovingBitmap Story;							// �@��
	CMovingBitmap Background;						// �I��
	CMovingBitmap Actress;							// �k�D��
	CMovingBitmap Actor;							// �D��
	CMovingBitmap Temp1;							// �]�s�M��
	CMovingBitmap Temp2;							// �]�s�M��
	CMovingBitmap Temp3;							// �]�s�M��
	CMovingBitmap Temp4;							// �]�s�M��
	int cursor_x, cursor_y;
	int menu_index;
	int total_menu;
	int about_y;
	int story;
	int i;
	char t1[80] = "";
	char t2[80] = "";
	char t3[80] = "";
	char t4[80] = "";
	char t5[80] = "";
	char t6[80] = "";
	bool tutorialIsOpen;
	bool enterFoolproof;
	bool aboutIsOpen;
	bool storyIsOpen;
	bool jumpStory;									// ���L�@��
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState
{
public:
	CGameStateRun(CGame *g);
	~CGameStateRun();
	void OnBeginState();				// �]�w�C�������һݪ��ܼ�
	void OnInit();  					// �C������Ȥιϧγ]�w
	void OnKeyDown(UINT, UINT, UINT);
	void OnKeyUp(UINT, UINT, UINT);
	void End();
protected:
	bool DoingSomeing();
	void OnMove();						// ���ʹC������
	void OnBattle();
	void OnAudio();
	Monster *RandomMonster();
	void OnShow();						// ��ܳo�Ӫ��A���C���e��
	void ShowHeroUi();
private:
	BattleUI			battleUI;		// �԰�����
	Hero				hero;			// ��l
	Monster				*monster;		// �Ǫ�
	Skull				*skull;			// ���\
	FlyingEye			*flyingEye;	    // �j��
	Goblin				*goblin;		// �����L
	Mushsroom			*mushsroom;		// ��ۣ�H
	Behemoth            *behemoth;
	vector<unique_ptr<Npc>>	npc;		// �ӤH
	vector<unique_ptr<Chest>>	chest;
	CInteger			printNum;		// �ͩR
	AdjustableCInteger	NumberUI;
	GameMap				gamemap;		// �a��
	bool				isBattling;
	bool				isCollision;
	bool				playWalkTheme;
	bool				end;
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState
{
public:
	CGameStateOver(CGame *g);
	void OnBeginState();	  	// �]�w�C�������һݪ��ܼ�
	void OnInit();
protected:
	void OnMove();			  	// ���ʹC������
	void OnShow();			  	// ��ܳo�Ӫ��A���C���e��
private:
	CMovingBitmap Background;
	int counter;				// �˼Ƥ��p�ƾ�
};

}